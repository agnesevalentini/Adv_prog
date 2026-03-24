# This is a python script that tests that the C++ statistics_module functionalities can be used in Python
import sys
sys.path.append("/home/agnese/miniconda3/lib/python3.12/site-packages") # path to the site-packages folder
import pandas as pd
import classification_operations 
import statistics_module # importing the C++ module

def python_test():

    # testing the C++ module
    reader: statistics_module.CSVReader = statistics_module.CSVReader()
    reader.parse_arguments(["statistics_module","Depression_Student_Dataset.csv"])
    reader.load_data()
    reader.print_column(1) 
    reader.print_row(2)
    reader.write_statistics_to_file("stats.txt")
    print("Statistics and histogram written to: stats.txt")

    # testing the Python class
    data: pd.dataFrame = reader.to_pandas()
    mean_values = data["Age"].astype(float).tolist() # convert the column to a list of floats
    print(data["Depression"].value_counts())
    print(data["Dietary Habits"].value_counts())
    classification: classification_operations = classification_operations.classification_operations(data, "Depression", 0.2)
    classification.train()
    print(classification.evaluate())
    classification.feature_importances()
    print(classification.confusion_matrix())
    print(classification.classification_report())
    #classification.roc_curve()
    classification.histogram("Age")
    

if __name__ == '__main__':
    python_test()

