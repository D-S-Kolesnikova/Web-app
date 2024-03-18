
from flask import Flask, redirect, url_for, render_template, request
import os
import subprocess
from ctypes import *
import ctypes

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/login", methods=["POST", "GET"])
def login():
    if request.method == "POST":
        user = request.form["nm"]
        return redirect(url_for("user", usr=user))
    else:
        return render_template("login.html")

@app.route("/<usr>")
def user(usr):
    return f"<h1>{usr}</h1>"

@app.route("/exe", methods=["POST", "GET"])
def exe():
    if request.method == "POST":
        if request.form['submit'] == 'runFile':
            current_dir = os.getcwd()
            Missile = WinDLL(current_dir + "/Missile-dll.dll")
            Missile.MissileModelling.argtypes = [
                ctypes.c_double,  # x0
                ctypes.c_double,  # y0
                ctypes.c_double,  # v0
                ctypes.c_double,  # tet0
                ctypes.c_double,  # mass
                ctypes.c_double,  # cx
                ctypes.c_double,  # d
                ctypes.POINTER(ctypes.c_double),  # outX
                ctypes.POINTER(ctypes.c_double),  # outY
                ctypes.POINTER(ctypes.c_int)  # size
            ]
            size = ctypes.c_int()
    
            # Assuming a maximum size for the output arrays
            max_size = 1000
            outX = (ctypes.c_double * max_size)()
            outY = (ctypes.c_double * max_size)()
            
            x0, y0, v0, tet0, mass, cx, d = 0.0, 0.0, 100.0, 45.0, 10.0, 0.1, 0.5
            Missile.MissileModelling(x0, y0, v0, tet0, mass, cx, d, outX, outY, ctypes.byref(size))
            
            # Convert the C arrays to Python lists
            outX_list = [outX[i] for i in range(size.value)]
            outY_list = [outY[i] for i in range(size.value)]
            print(outX_list, outY_list)
            
            return render_template('assemblies.html', text=outX_list[3])
    else:
        return render_template("assemblies.html")

if __name__ == "__main__":
    app.run(debug=True)