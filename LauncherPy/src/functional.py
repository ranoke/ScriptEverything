import os
import requests
import json
import urllib.request
import zipfile
import psutil
import subprocess

github = "https://api.github.com"
releases = "/repos/ranoke/ScriptEverything/releases" # GET request



def download():
    headers = {'Accept': 'application/vnd.github.v3+json1'}
    ret = requests.get(github + releases, headers=headers) 
    j = json.loads(ret.text)
    last_release = j[0]['assets'][0]['browser_download_url']
    urllib.request.urlretrieve(last_release, 'temp_release.zip') 
    with zipfile.ZipFile("temp_release.zip","r") as zip_ref:
        zip_ref.extractall("C:/ScriptEverything")
    os.remove("temp_release.zip")

def inject(name):
    #name = "ac_client.exe"

    print("injecting")
    print(f"name is {name}")
    subprocess.call(f"C:\\ScriptEverything\\bin\\Release-32\\Injector.exe 1 {name} C:\\ScriptEverything\\bin\\Release-32\\Engine.dll")

