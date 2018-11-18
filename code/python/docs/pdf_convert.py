from fpdf import FPDF
 
def pdf_convert(fname, data):
    pdf = FPDF()
    pdf.set_margins(left=10, top=15, right=10)
    pdf.add_page()
    pdf.add_font('calibri', fname=r'c:\Windows\Fonts\calibri.ttf', uni=True)
    pdf.image('gables.jpg', x=90, w=30)
    pdf.set_font("calibri", size=12)
    pdf.multi_cell(0, 5, txt=data)
    pdf.output(fname)
