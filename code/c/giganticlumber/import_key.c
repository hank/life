/* GiganticLumber: Import Key */
// Imports a key given in the query string.

#include <gpgme.h>
#include <time.h>
#include <stdio.h>   
#include <string.h>   
#include <stdlib.h>  
#include <errno.h> 
#include <locale.h>
#include <sqlite3.h>
#include "support.h"

// 256K Bufer
#define SIZE (1<<18)

/* USE -D_FILE_OFFSET_BITS=64 (at least) on Debian!  */
int initialize_context(gpgme_ctx_t *);

int main()
{
  char *bptr, *query_string, *content_len, *primary_email;
  char *buf, *strkey, *strsignkeyid;
  int clen, found;
  char * pKey, *pVal, *pEnd;
  int keylen, vallen, printed = 0;
  size_t read_bytes;
  char timebuf[60];

  /* GPGME Variables */
  gpgme_ctx_t ceofcontext;
  gpgme_error_t err;
  gpgme_data_t rdata;
  gpgme_import_result_t import_result;
  gpgme_key_t key;
  gpgme_user_id_t uid;
  gpgme_key_sig_t sig;

  printf("Content-type: text/html\r\n\r\n"); fflush(stdout);

  // Check that we're posting information
  if(strncmp(getenv("REQUEST_METHOD"), "POST", 4) != 0) {
    printf("<p><b>Usage:</b> POST with key=&lt;keyid&gt;</p>");
    fflush(stdout);
    return 0;
  }

  // We have a POST!
  content_len = getenv("CONTENT_LENGTH");
  if(!content_len) {
    // Failed to find it
    printf("<p>Content Length not specified.  Please use the POST method.</p>");
    fflush(stdout);
    return 0;
  }
  clen = strtol(content_len, NULL, 10);

  if(errno == ERANGE) {
    // strtol parse error
    printf("<p>Content Length Invalid</p>");
    fflush(stdout);
    return 0;
  }

  // Allocate enough space for junk.
  if(clen > SIZE - 1) {
    // Uhoh, we don't have enough space for that key.
    // The princess is in another castle!
    printf("<p>Content Length Too large (%d), maximum %u</p>", clen, SIZE - 1);
    fflush(stdout);
    return 0;
  }

  // Read in the key.
  buf = malloc(clen + 1);
  bptr = buf;
  while(!feof(stdin) && bptr < &buf[clen]) {
    read_bytes = fread(bptr, 1, 4096, stdin);
    bptr += read_bytes;
    //printf("<p>Read %ld bytes into buf</p>", read_bytes);
    if(ferror(stdin)) {
      // Weird error reading STDIN
      printf("<p>Error reading key file stream.</p>");
      fflush(stdout);
      return 0;
    }
  }
  if(bptr > &buf[clen]) {
    // They lied!  The key is too big to be imported!
    printf("<p>Content Length does not match key size, or EOF not sent. (%ld vs %d)</p>", bptr - buf, clen);
    fflush(stdout);
    return 0;
  }
  *bptr++ = '0';

  // Decode and stuff
  fflush(stdout);
  bptr = buf;
  while(1) {
    // Set key
    pKey = bptr;
    // find =
    for(; *bptr && *bptr != '='; bptr++);
    if(*bptr == '\0') {
      // We're done here.  It was one long key...
      printf("<p>Error parsing POST DATA.</p>");
      fflush(stdout);
      return 0;
    }
    keylen = bptr - pKey;
    // Set val
    pVal = bptr + 1;
    if(*pVal == '\0') {
      // We're done here.  It was one long key...
      printf("<p>Error parsing POST DATA.</p>");
      fflush(stdout);
      return 0;
    }
    // find & or 0
    for(; *bptr && *bptr != '&'; bptr++);
    vallen = bptr - pVal;
    // Do the magic
    if(strncmp("key=", pKey, keylen+1) == 0) {
      strkey = malloc(vallen+1);
      memcpy(strkey, pVal, vallen);
      strkey[vallen] == '0';
      URLDecode(strkey);
    }
    else if(strncmp("signer_key=", pKey, keylen+1) == 0) {
      if(pVal[0] == '0' && 
          (pVal[1] == 'x' || strsignkeyid[1] == 'X')
        ) {
         vallen -= 2;
         pVal += 2; 
      }
      if(vallen != 8 && vallen != 16) {
        printf("<p>Invalid Signer Key ID.  Formatting like any of the following will do:</p>");
        printf("<ul>");
        printf("<li>F693F0F246C171A0</li>");
        printf("<li>46C171A0</li>");
        printf("<li>0xF693F0F246C171A0</li>");
        printf("<li>0x46C171A0</li>");
        printf("</ul>");
        fflush(stdout);
        return 0;
      }
      strsignkeyid = malloc(vallen+1);
      memcpy(strsignkeyid, pVal, vallen);
      strsignkeyid[vallen] == '0';
      URLDecode(strsignkeyid);
      printf("</p>Signer Key: %s<p>", strsignkeyid, strlen(strsignkeyid));
    }
    if(*bptr == '\0') {
      // We're done here.  Last value
      break;
    }
    bptr++;
  }

  err = initialize_context(&ceofcontext);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err;

  /* set encoding for the buffer... */
  //err = gpgme_data_set_encoding(rdata,GPGME_DATA_ENCODING_ARMOR);
  //if(err != GPG_ERR_NO_ERROR) goto gpg_err;

  err = gpgme_set_keylist_mode(ceofcontext, GPGME_KEYLIST_MODE_SIGS);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err;

  /* create buffer for data exchange with gpgme*/
  err = gpgme_data_new_from_mem(&rdata, strkey, strlen(strkey), 0);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err;

  /* Import the key */
  err = gpgme_op_import(ceofcontext, rdata);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err;

  import_result = gpgme_op_import_result(ceofcontext);
  if(import_result->considered == 0) {
    printf("<p>Zero keys imported.</p>"); 
    fflush(stdout);
    return 0;
  }
  printf("<p>Key %s Imported</p>", import_result->imports[0].fpr); 
  fflush(stdout);

  err = gpgme_get_key(ceofcontext, import_result->imports[0].fpr,
      &key, 0);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err;

  uid = key->uids;
  if(!uid) {
    printf("<p>No UIDs found.  Please check key</p>");
    fflush(stdout);
    return 0;
  }

  // Get the primary UID email.
  primary_email = key->uids[0].email;
  printf("<ul>");
  do {
    sig = uid->signatures;
    if(!sig) continue;
    do {
      if((strcasecmp(sig->keyid, strsignkeyid) == 0) ||
         (strcasecmp(&sig->keyid[8], strsignkeyid) == 0)
        ) {
        // This UID is signed.

        // We don't care about revoked UIDs.
        if(uid->revoked || uid->invalid) break;
        if(!printed) {
          // Print relavent UID information
          printf("<li>%s ", uid->name);
          if(uid->email) printf("&lt;%s&gt; ", uid->email);
          if(uid->comment) printf("(%s) ", uid->comment);
          printf("<ul>");
          fflush(stdout);
          printed = 1;
        }
        // Print relevent signature information
        printf("<li>%s ", sig->keyid);
        switch(sig->sig_class) {
          case 0x10:
            printf("Generic Level ");
            break;
          case 0x11:
            printf("<span style=\"color: #880000;\">Persona Level</span> ");
            break;
          case 0x12:
            printf("<span style=\"color: #000088;\">Casual Level</span> ");
            break;
          case 0x13:
            printf("<span style=\"color: #008800;\">Positive Level</span> ");
            break;
        }
        if(sig->revoked) printf("<b>Revoked</b> ");
        if(sig->expired) printf("<b>Expired</b> ");
        if(sig->invalid) printf("<b>Invalid</b> ");
        if(!sig->exportable) printf("<b>Non-exportable</b> ");
        printf("Signature ");
        if(sig->timestamp != 0 && sig->timestamp != -1) { 
          strftime(timebuf, 59, "%Y/%m/%d %H:%M:%S %Z", gmtime(&sig->timestamp));
          printf("Made on %s ", timebuf);
        } 
        if(sig->expires != 0) { 
          strftime(timebuf, 59, "%Y/%m/%d %H:%M:%S %Z", gmtime(&sig->expires));
          printf("Expires on %s", timebuf);
        } 
        printf("</li>");
        
        fflush(stdout);
      }
    } while((sig = sig->next) != NULL);
    if(printed) printf("</ul></li>");
    printed = 0;
  } while((uid = uid->next) != NULL);
  printf("</ul>");
  fflush(stdout);

  // Give the use an offer they can't refuse.
  printf("<h3>Does this look correct?</h3>"
         "<p>If not, hit your browser's back button and try again.</p>"
         "<p>If it does look alright, put in your email and you'll be "
         "notified when the other party reciprocates. "
         "We'll also notify the other party via their primary email (%s).</p>"
         "<form method=\"post\" action=\"save_exchange.php\">"
           "<label>Email</label>"
           "<input type=\"text\" name=\"signer_email\" />"
           "<input type=\"text\" name=\"signee_email\" value=\"%s\"/>"
           "<input type=\"text\" name=\"signer_key\" value=\"%s\"/>"
           "<input type=\"text\" name=\"signee_key\" value=\"%s\"/>"
           "<input type=\"submit\" value=\"Notify Me\" />"
         "</form>",
         primary_email,
         primary_email,
         strsignkeyid,
         &import_result->imports[0].fpr[24]
  );

  /* free data */
  gpgme_data_release(rdata);

  /* free context */
  gpgme_release(ceofcontext);

  return 0;

gpg_err:
  printf("<p>GPG Error</p>");
  fflush(stdout);
  return 0;
}

int initialize_context(gpgme_ctx_t * ceofcontext)
{
  char *p;
  gpgme_error_t err;
  gpgme_engine_info_t enginfo;
  /* The function `gpgme_check_version' must be called before any other
   * function in the library, because it initializes the thread support
   * subsystem in GPGME. (from the info page) */
  setlocale (LC_ALL, "");
  p = (char *) gpgme_check_version(NULL);
  //printf("version=%s\n",p); fflush(stdout);
  /* set locale, because tests do also */
  gpgme_set_locale(NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));

  /* check for OpenPGP support */
  err = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err_2;

  p = (char *) gpgme_get_protocol_name(GPGME_PROTOCOL_OpenPGP);
  //printf("Protocol name: %s\n",p); fflush(stdout);

  /* create our own context */
  err = gpgme_new(ceofcontext);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err_2;

  err = gpgme_ctx_set_engine_info (*ceofcontext, GPGME_PROTOCOL_OpenPGP,
      NULL, "/var/www/.gnupg");
  if(err != GPG_ERR_NO_ERROR) goto gpg_err_2;

  /* get engine information */
  err = gpgme_get_engine_info(&enginfo);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err_2;

  //printf("file=%s, home=%s\n",enginfo->file_name,enginfo->home_dir); fflush(stdout);
  //fflush(stdout);

  /* set protocol to use in our context */
  err = gpgme_set_protocol(*ceofcontext,GPGME_PROTOCOL_OpenPGP);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err_2;

  err = gpgme_ctx_set_engine_info (*ceofcontext, GPGME_PROTOCOL_OpenPGP,
      enginfo->file_name,enginfo->home_dir);
  if(err != GPG_ERR_NO_ERROR) goto gpg_err_2;

  /* do ascii armor data, so output is readable in console */
  gpgme_set_armor(*ceofcontext, 1);

  return GPG_ERR_NO_ERROR;

gpg_err_2:
  printf("<p>GPG Error: %s</p>", gpgme_strerror(err)); fflush(stdout);
  return err;
}
