GenderRecognizer
================
This is a gender recognition library for OpenCV written in C++.

It uses FaceRecognizer class and Facial landmark locator library (http://cmp.felk.cvut.cz/~uricamic/flandmark/).

GenderRecognizer class: 

1.)predict(face) predicts gender from face image, returns 0 for male and 1 for female 
2.)update(face) predicts gender based on multiple face images weighted with confidence.
