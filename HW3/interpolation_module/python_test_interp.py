#Python script

import pandas as pd
import Interpolation as int
import matplotlib.pyplot as plt  #for the plots
import numpy as np #for the interpolation x values
from PythonFunctions import read_data, int_preprocessing, df_to_array, plot_interpolations


### ++++++++++++++++++++++++++++++++++++++++++++++++
# Read data from a file:
df= read_data('data.csv')

#Inspection: all possible descriptive statistics, general dataframe summary:
print(df.columns)
print(df.info())
print(df.describe())

#Data preprocessing:
df_proc=int_preprocessing(df, 'v', 'r', 'mean')

#Conversion: from dataframe to array (to exploit pybind built-in type conversion between C++ and Python):
a= df_to_array(df, 0)
b= df_to_array(df, 1)
print(a)
print(b)

#Interpolation, calling C++ classes:
LI= int.LinearInterpolation(a, b, 'data.csv')
LAGI = int.LagrangeInterpolation(a, b, 'data.csv')
NWI = int.NewtonInterpolation(a, b, 'data.csv')
LI.printVectors() #print the vectors of x and y values, all the same for the three objects
checkextremes_LI = LI.getExtremes #get the extremes of the x values, all the same for the three objects
print(checkextremes_LI)

#Test interpolation, given a vector of x values we get the interpolated y values for different interpolation methods(different objects):
vector = [290, 350, 450, 710, 850, 1500, 1800]
Tinterp_LI= LI(vector)
Tinterp_LAGI= LAGI(vector)
Tinterp_NWI= NWI(vector)
print(Tinterp_LI,'\n',Tinterp_LAGI, '\n', Tinterp_NWI)

#Plotting:
#Vector for interpolation, support for the plot is the interval of the x values (and conversion to a pandas series)
vector=np.arange(checkextremes_LI[0],checkextremes_LI[1],0.1)
vector=pd.Series(vector)
#Different interpolation methods
interp_LI= LI(vector)
interp_LAGI= LAGI(vector)
interp_NWI= NWI(vector)
#plots
plot_interpolations(a,b,vector, interp_LI, title='Linear Interpolation', label='Linear Interpolation', marker = '+', markersize=1)
plot_interpolations(a,b,vector, interp_LAGI, title='Lagrange Interpolation', label='Lagrange Interpolation', marker = '+', markersize=1)
plot_interpolations(a,b,vector, interp_NWI, title='Newton Interpolation', label='Newton Interpolation', marker = '+', markersize=1)
#cropped x vector to better visualize Lagrange and Newton interpolations
vector_cropped=np.arange(checkextremes_LI[0],1200,0.1)
vector_cropped=pd.Series(vector_cropped)
interp_LAGI_cropped= LAGI(vector_cropped)
interp_NWI_cropped= NWI(vector_cropped)
plot_interpolations(a,b,vector_cropped, interp_LAGI_cropped, title='Lagrange Interpolation', label='Lagrange Interpolation', marker = '+', markersize=1)
plot_interpolations(a,b,vector_cropped, interp_NWI_cropped, title='Newton Interpolation', label='Newton Interpolation', marker = '+', markersize=1)





#poi correggi funzione preprocessing 












