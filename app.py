
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
            Missile = cdll.LoadLibrary(current_dir + "/missile.so")
            #Missile = WinDLL(current_dir + "/Missile-dll.dll")
            Missile.MissileModelling.argtypes = [
                ctypes.c_float,  # x0
                ctypes.c_float,  # y0
                ctypes.c_float,  # v0
                ctypes.c_float,  # tet0
                ctypes.c_float,  # mass
                ctypes.c_float,  # cx
                ctypes.c_float,  # d
                ctypes.POINTER(ctypes.c_float),  # outT
                ctypes.POINTER(ctypes.c_float),  # outVx
                ctypes.POINTER(ctypes.c_float),  # outVy
                ctypes.POINTER(ctypes.c_float),  # outX
                ctypes.POINTER(ctypes.c_float),  # outY
                ctypes.POINTER(ctypes.c_float),  # outTeta
                ctypes.POINTER(ctypes.c_int)  # size
            ]
            size = ctypes.c_int()
    
            # Assuming a maximum size for the output arrays
            max_size = 10000
            outT = (ctypes.c_float * max_size)()
            outVx = (ctypes.c_float * max_size)()
            outVy = (ctypes.c_float * max_size)()
            outX = (ctypes.c_float * max_size)()
            outY = (ctypes.c_float * max_size)()
            outTeta = (ctypes.c_float * max_size)()

            x0 = float(request.form['X'])
            y0 = float(request.form['Y'])
            v0 = float(request.form['V0'])
            tet0 = float(request.form['TETA'])
            mass = float(request.form['M'])
            cx = float(request.form['Cx'])
            d = float(request.form['D'])
            #x0, y0, v0, tet0, mass, cx, d = 0.0, 0.0, 100.0, 45.0, 10.0, 0.1, 0.5
            Missile.MissileModelling(x0, y0, v0, tet0, mass, cx, d, outT, outVx, outVy, outX, outY, outTeta, ctypes.byref(size))
            
            # Convert the C arrays to Python lists
            outT_list = [outT[i] for i in range(size.value)]
            outVx_list = [outVx[i] for i in range(size.value)]
            outVy_list = [outVy[i] for i in range(size.value)]
            outX_list = [outX[i] for i in range(size.value)]
            outY_list = [outY[i] for i in range(size.value)]
            outTeta_list = [outTeta[i] for i in range(size.value)]

            flat_list = list(zip(outT_list, outVx_list, outVy_list, outX_list, outY_list, outTeta_list))
            return render_template('results.html', list=flat_list)
        
        if request.form['submit'] == 'writeFigure':
            current_dir = os.getcwd()
            Missile = cdll.LoadLibrary(current_dir + "/missile.so")
            #Missile = WinDLL(current_dir + "/Missile-dll.dll")
            Missile.MissileModelling.argtypes = [
                ctypes.c_float,  # x0
                ctypes.c_float,  # y0
                ctypes.c_float,  # v0
                ctypes.c_float,  # tet0
                ctypes.c_float,  # mass
                ctypes.c_float,  # cx
                ctypes.c_float,  # d
                ctypes.POINTER(ctypes.c_float),  # outT
                ctypes.POINTER(ctypes.c_float),  # outVx
                ctypes.POINTER(ctypes.c_float),  # outVy
                ctypes.POINTER(ctypes.c_float),  # outX
                ctypes.POINTER(ctypes.c_float),  # outY
                ctypes.POINTER(ctypes.c_float),  # outTeta
                ctypes.POINTER(ctypes.c_int)  # size
            ]
            size = ctypes.c_int()
    
            # Assuming a maximum size for the output arrays
            max_size = 10000
            outT = (ctypes.c_float * max_size)()
            outVx = (ctypes.c_float * max_size)()
            outVy = (ctypes.c_float * max_size)()
            outX = (ctypes.c_float * max_size)()
            outY = (ctypes.c_float * max_size)()
            outTeta = (ctypes.c_float * max_size)()

            x0 = float(request.form['X'])
            y0 = float(request.form['Y'])
            v0 = float(request.form['V0'])
            tet0 = float(request.form['TETA'])
            mass = float(request.form['M'])
            cx = float(request.form['Cx'])
            d = float(request.form['D'])
            #x0, y0, v0, tet0, mass, cx, d = 0.0, 0.0, 100.0, 45.0, 10.0, 0.1, 0.5
            Missile.MissileModelling(x0, y0, v0, tet0, mass, cx, d, outT, outVx, outVy, outX, outY, outTeta, ctypes.byref(size))
            
            # Convert the C arrays to Python lists
            outT_list = [outT[i] for i in range(size.value)]
            outVx_list = [outVx[i] for i in range(size.value)]
            outVy_list = [outVy[i] for i in range(size.value)]
            outX_list = [outX[i] for i in range(size.value)]
            outY_list = [outY[i] for i in range(size.value)]
            outTeta_list = [outTeta[i] for i in range(size.value)]
            return render_template('printFigure.html', outX_list=outX_list, outY_list=outY_list)
    else:
        return render_template("assemblies.html")
    

if __name__ == "__main__":
    app.run(debug=True)