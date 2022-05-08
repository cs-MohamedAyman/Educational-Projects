from random import randint
import cv2
import dlib

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor('shape_predictor_68_face_landmarks.dat')
googly_eyes_path = 'googly_eye.png'
googly_eyes = cv2.imread(googly_eyes_path)

def draw_eye(img, shapes, start, end):
    min_x, max_x, min_y, max_y = 2e9, 0, 2e9, 0
    for n in range(start,end):
        min_x = min(min_x, shapes.part(n).x)
        min_y = min(min_y, shapes.part(n).y)
        max_x = max(max_x, shapes.part(n).x)
        max_y = max(max_y, shapes.part(n).y)
    h = int(max(max_x-min_x, max_y-min_y))
    w = int(max(max_x-min_x, max_y-min_y))
    curr_googly = cv2.resize(googly_eyes, (w, h))
    curr_googly = [cv2.rotate(curr_googly, cv2.cv2.ROTATE_90_CLOCKWISE),
                   cv2.rotate(curr_googly, cv2.cv2.ROTATE_180),
                   cv2.rotate(curr_googly, cv2.cv2.ROTATE_90_COUNTERCLOCKWISE),
                   curr_googly][randint(0, 3)]
    min_y -= int(min_y*.05)
    img[min_y:min_y+w, min_x:min_x+h, :3] = curr_googly

def execute_model(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = detector(gray)
    for face in faces:
        shapes = predictor(gray, face)
        draw_eye(img, shapes, 36, 42)
        draw_eye(img, shapes, 42, 48)
    return img
