from MyPython import Input as Inp
import numpy as np
import argparse
import subprocess
import os.path as path
import sys


VERSION="1.0"


par=argparse.ArgumentParser(description="Execute AWK code on a file while creating logs of the process.")
par.add_argument("awk_file", help="The file containing the AWK source code")
par.add_argument("source_file", help="The file containing the input data")
par.add_argument("result_file", help="The file to write the GAWK output. Overwritten, or created if not existent")
args=par.parse_args()
inp=Inp.Input(None, VERSION)

try:
    f = open(args.result_file, "w+")
    subprocess.check_call(["gawk", "-f", args.awk_file, args.source_file], stdout=f)
except subprocess.CalledProcessError as cpe:
    print("Called subprocess returned with exit code "+str(cpe.returncode))
    sys.exit()

inp.write_log(args.result_file, args.source_file, file_ext=".log")
