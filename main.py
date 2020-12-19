import face_recognition as fr
import os

def get_encoded_faces():
    encoded = {}
    for _, _, fnames in os.walk("images/"):
        for f in fnames:
            if f.endswith(".jpg") or f.endswith(".png"):
                face = fr.load_image_file("faces/" + f)
                encoding = fr.face_encodings(face)[0]
                encoded[f.split(".")[0]] = encoding

    return encoded


print(get_encoded_faces())
