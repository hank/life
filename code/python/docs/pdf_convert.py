from fpdf import FPDF
 
def pdf_convert(fname, data):
    pdf = FPDF()
    pdf.set_margins(left=10, top=15, right=10)
    pdf.add_page()
    pdf.set_font("Arial", size=12)
    pdf.multi_cell(0, 5, txt=data)
    pdf.output(fname)
