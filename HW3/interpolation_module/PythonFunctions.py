import pandas as pd
import os
import Interpolation as int
import matplotlib.pyplot as plt  #for the plots
import numpy as np #for the interpolation x values



### ++++++++++++++++++++++++++++++++++++++++++++++++
# Function to read data from a file
def read_data(file_path):
    file_extension = os.path.splitext(file_path)[1] # Get the file extension
    
    if file_extension == '.csv':
        df = pd.read_csv(file_path)
        if df.empty:
            raise ValueError("No data found")
    elif file_extension == '.xlsx' or file_extension == '.xls':
        df = pd.read_excel(file_path)
        if df.empty:
            raise ValueError("No data found")
    elif file_extension == '.json':
        df = pd.read_json(file_path)
        if df.empty:
            raise ValueError("No data found")
    else:
        raise ValueError("Unsupported file format")
    return df



#Function to preprocess a COPY of the data frame. The 'duplicates_handling' parameter can be set to min, max or mean, mean being the default. x, y and duplicates_handling must be set as strings.
def int_preprocessing(df,x,y,duplicates_handling):
    df = df.copy()
    #print deleted obs for missing x and duplicate x found and solved
    print('-----\n','Preprocessing results:')

    #missing values
    print('Deleted missing values:', df.isnull().sum())
    #delete missing values
    df.dropna(inplace=True)
    #duplicate values
    print('x duplicates handled by', duplicates_handling, ':', df.duplicated(subset = x).sum(), "\n-----")
    #handle duplicates of x ...the mean of the y values
    if duplicates_handling == 'min':
        df = df.groupby(x, as_index=False)[y].min()
    elif duplicates_handling == 'max':
        df = df.groupby(x, as_index=False)[y].max()
    elif duplicates_handling == 'mean' or duplicates_handling == '':
        df = df.groupby(x, as_index=False)[y].mean()
    else:
        raise ValueError("Unsupported duplicates handling method")
    return df



#Function to convert a column of a dataframe to an array
def df_to_array(df, column): #we loose column labels
    col_to_arr = df.iloc[:,column].to_numpy() #indices (column) from 0
    return col_to_arr



# Function to plot the original data points and the interpolated results
def plot_interpolations(x, y, vector, y_interp, title='', label='',linestyle='', marker='', markersize=None):
    plt.figure(figsize=(10, 6))

    #originals
    bind = pd.DataFrame({
    'x': x,
    'y': y  
    })
    bind.sort_values(by='x', inplace=True)
    x = bind['x']
    y = bind['y']
    plt.plot(x, y, label='Original datapoints', linestyle='', marker='o')
    
    # Plot interpolated results
    plt.plot(vector, y_interp, label=label, linestyle=linestyle, marker=marker, markersize=markersize)
    
    # Add titles and labels
    plt.title(title)
    plt.xlabel('X values')
    plt.ylabel('Y values')
    plt.legend()
    plt.grid(True)
    
    # Show plot
    plt.show()



    

