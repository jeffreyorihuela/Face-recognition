import face_recognition as fr
from rtree import index
import os
import json
from flask import Flask
from flask_cors import cross_origin, CORS
from flask import request
from flask import abort
from flask import send_file

def get_encoded_faces(idx, count_images):
    encoded = {}
    for dirpath, dnames, fnames in os.walk("images/"):
        print("fnames ", fnames)
        for f in fnames:
            print("file ", f)
            if f.endswith(".jpg") or f.endswith(".png"):
                count_images = count_images + 1
                face = fr.load_image_file(dirpath+'/'+f)
                
                encoding = fr.face_encodings(face)

                if len(encoding) > 0:
                    encoded[f.split(".")[0]] = encoding[0]
                    idx.insert(count_images, encoding[0].tolist(), dirpath+'/'+f)

    return encoded

p = index.Property()
p.dimension = 128
p.dat_extension = 'data'
p.idx_extension = 'index'
idx = index.Index('128d_index', properties=p)

#Uncomment following lines to compile data set

#count_images = 0
#faces = get_encoded_faces(idx, count_images)
#print(faces.keys())

UPLOAD_FOLDER = "./uploads"
ALLOWED_EXTENSIONS = {'txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'}

app=Flask(__name__)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/', methods = ['POST'])
@cross_origin()
def similar():
    k = request.values['k']
    file = request.files['image']
    if file and allowed_file(file.filename):

        file.save(os.path.join(app.config['UPLOAD_FOLDER'], file.filename))
        face = fr.load_image_file(UPLOAD_FOLDER+'/'+file.filename)
        encoding = fr.face_encodings(face)[0]
        print(len(encoding.tolist()))
        hits = list(idx.nearest(encoding.tolist(), int(k), objects="raw"))
        for item in hits:
            print(item)


        return json.dumps({'results': hits}), 200, {'ContentType':'application/json'}
        
    return json.dumps({'success':True}), 200, {'ContentType':'application/json'}


@app.route('/get-photo', methods = ['POST'])
@cross_origin()
def get_photo():
    path = request.values['path']
    print("PATH __ ")
    print(path)
    return send_file(path)