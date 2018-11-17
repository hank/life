from __future__ import print_function
import sys
import httplib2
import os
from parse_homeowners import parse_homeowners
from pdf_convert import pdf_convert

from apiclient import discovery
from oauth2client import client
from oauth2client import tools
from oauth2client.file import Storage

# If modifying these scopes, delete your previously saved credentials
# at ~/.credentials/drive-python-quickstart.json
SCOPES = 'https://www.googleapis.com/auth/drive'
CLIENT_SECRET_FILE = 'client_secret.json'
APPLICATION_NAME = 'Drive API Python Quickstart'


def get_credentials():
    """Gets valid user credentials from storage.

    If nothing has been stored, or if the stored credentials are invalid,
    the OAuth2 flow is completed to obtain the new credentials.

    Returns:
        Credentials, the obtained credential.
    """
    home_dir = os.path.expanduser('~')
    credential_dir = os.path.join(home_dir, '.credentials')
    if not os.path.exists(credential_dir):

        os.makedirs(credential_dir)
    credential_path = os.path.join(credential_dir,
                                   'drive-python-quickstart.json')

    store = Storage(credential_path)
    credentials = store.get()
    if not credentials or credentials.invalid:
        flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
        flow.user_agent = APPLICATION_NAME
        if flags:
            credentials = tools.run_flow(flow, store, flags)
        else: # Needed only for compatibility with Python 2.6
            credentials = tools.run(flow, store)
        print('Storing credentials to ' + credential_path)
    return credentials

def main(homeowners_fpath, outdir, fmat="TXT"):
    """Shows basic usage of the Google Drive API.

    Creates a Google Drive API service object and outputs the names and IDs
    for up to 10 files.
    """
    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    service = discovery.build('drive', 'v3', http=http)

    results = service.files().list(
        pageSize=10,fields="nextPageToken, files(id, name, mimeType)").execute()
    items = results.get('files', [])
    if not items:
        print('No files found.')
    else:
        print('Files:')
        i = 0
        for item in items:
            print('{0}: {1} ({2})'.format(i, item['name'], item['id']))
            i += 1
    num = int(input("Item number: ").strip())
    results = service.files().export(fileId=items[num]['id'], mimeType='text/csv').execute()
    with open("out.csv", "wb") as f:
        f.write(results)
    # print(results)
    import csv
    # import io
    # csvIn = io.StringIO(str(results), newline='')
    with open("out.csv", "r") as f:
        reader = csv.reader(f)
        reader = list(reader)
    labels = reader[0]
    print(labels)

    with open("letter_template.txt", "r") as template:
        letter_template = template.read()

    try:
        os.makedirs(outdir)
    except:
        pass

    homeowners = parse_homeowners(homeowners_fpath)
    addresses = {x['Street Address'].strip(): x['Last Name'] for x in homeowners}
    for row in reader[1:]:
        # Attempt to find address in homeowners
        if row[labels.index('Inspection Address')] not in addresses:
            raise RuntimeError("ERROR, couldn't find {} in addresses".format(row[labels.index('Inspection Address')]))
        lastname = addresses[row[labels.index('Inspection Address')]].strip()
        insp_arr = []
        for idx, field in enumerate(row):
            if len(field) == 0:
                field = "None"
            insp_arr.append("{}: {}".format(labels[idx].strip(), field.strip()))
        inspection = "\n".join(insp_arr)
        message = letter_template.format(lastname=lastname, inspection=inspection)
        # Open a file with the address as the name and add fields to it
        fname = (row[labels.index('Inspection Address')].replace(r' ', '-').strip() + ".{}".format(fmat))
        if "pdf" == fmat:
            fullfname = os.path.join("inspections", fname)
            print("Creating {}".format(fullfname))
            pdf_convert(fullfname, message)

        else:
            print("Writing {}".format(fname))
            with open(os.path.join("inspections", fname), 'w') as f:
                f.write(message)
    if os.path.exists("out.csv"):
        print("Deleting temporary CSV")
        os.remove("out.csv")

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(parents=[tools.argparser])
    parser.add_argument("homeowners", help="TSV file containing homeowners information. Must be TAB delimited and the first row needs the column names.")
    parser.add_argument("--outdir", help="Output directory. Files will be overwritten if existing", default="inspections")
    parser.add_argument("--pdf", help="Make PDFs instead of TXT", action="store_true")
    args = parser.parse_args()
    if args.pdf:
        fmat="pdf"
    else:
        fmat="txt"
    main(args.homeowners, args.outdir, fmat=fmat)
