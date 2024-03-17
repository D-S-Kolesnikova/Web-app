
from flask import Flask, redirect, url_for, render_template, request
import os
import subprocess

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
            text = "... running ..."
            filepath="MINA.exe"
            subprocess.call(["missile/MINA.exe"])
            return render_template('assemblies.html', text=text)
    else:
        return render_template("assemblies.html")

if __name__ == "__main__":
    app.run(debug=True)