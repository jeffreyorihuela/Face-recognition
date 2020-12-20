import face_recognition as fr
from rtree import index
import os
from flask import Flask
from flask_cors import cross_origin
from flask import request
from flask import abort

def get_encoded_faces(idx, count_images):
    encoded = {}
    for dirpath, dnames, fnames in os.walk("images/"):
        for f in fnames:
            if f.endswith(".jpg") or f.endswith(".png"):
                count_images = count_images + 1
                face = fr.load_image_file(dirpath+'/'+f)
                encoding = fr.face_encodings(face)[0]
                encoded[f.split(".")[0]] = encoding
                idx.insert(count_images, encoding.tolist(), dirpath+'/'+f)

    return encoded

p = index.Property()
p.dimension = 128
p.dat_extension = 'data'
p.idx_extension = 'index'
idx = index.Index('128d_index', properties=p)

count_images = 0
#faces = get_encoded_faces(idx, count_images)
#print(faces.keys())

face = fr.load_image_file('Alejandro_Toledo_0004.jpg')
encoding = fr.face_encodings(face)[0]
print(len(encoding.tolist()))

hits = list(idx.nearest(encoding.tolist(), 3, objects="raw"))
for item in hits:
    print(item)

app=Flask(__name__)

@app.route('/', methods = ['POST'])
@cross_origin()
def similar():
    if request.files:
        print(request.files)
        image = request.files['image']
    return 