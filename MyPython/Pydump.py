#! python3
import xarray as xr
import sys
print(xr.open_dataset(sys.argv[1]))