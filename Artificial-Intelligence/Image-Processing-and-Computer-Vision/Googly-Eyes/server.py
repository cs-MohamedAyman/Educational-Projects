from flask import Flask, render_template, request
from PIL import Image
import numpy as np
import io
import base64
from model import execute_model

upload_page_path = "upload_page.html"
show_page_path   = "show_page.html"
image_type       = "PNG"
input_name       = 'original_image'
server_port      = 4000

app = Flask(__name__)

@app.route('/', methods = ['GET'])
def index():
    return render_template(upload_page_path)

@app.route('/converter', methods = ['POST'])
def upload_file():
    f = request.files[input_name]
    img = Image.open(f)
    img = np.array(img)
    img = execute_model(img)
    img = Image.fromarray(img)
    data_image = io.BytesIO()
    img.save(data_image, image_type)
    encoded_img = base64.b64encode(data_image.getvalue())
    decoded_img = encoded_img.decode('utf-8')
    return render_template(show_page_path, img_data=decoded_img)

if __name__ == '__main__' :
    app.run(port=server_port)
