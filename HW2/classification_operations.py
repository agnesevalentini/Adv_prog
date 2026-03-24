import sys
sys.path.append("/home/agnese/miniconda3/lib/python3.12/site-packages") # path to the site-packages folder

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, classification_report, roc_curve
from sklearn.preprocessing import LabelEncoder
import matplotlib.pyplot as plt
import numpy as np

# defining a class in Python that performs classification operations on a dataset
class classification_operations:
    def __init__(self, dataset: pd.DataFrame, target_column: str, test_size: float):
        self.dataset = dataset

        # transform the columns to numerical values
        self.dataset["Sleep Duration"] = dataset["Sleep Duration"].map({"Less than 5 hours": 0, "5-6 hours ": 1, "7-8 hours": 2, "More than 8 hours ": 3})
        self.dataset["Dietary Habits"] = dataset["Dietary Habits"].map({"Moderate": 1, "Unhealthy": 0, "Healthy":2})
        self.dataset["Gender"] = dataset["Gender"].map({"Male": 0, "Female": 1})
        self.dataset["Family History of Mental Illness"] = dataset["Family History of Mental Illness"].map({"No": 0, "Yes": 1})
        self.dataset["Have you ever had suicidal thoughts ?"] = dataset["Have you ever had suicidal thoughts ?"].map({"No": 0, "Yes": 1})
        self.target_column = target_column # define the target column
        self.test_size = test_size
        self.X = self.dataset.drop(columns=[self.target_column]) # define the features
        self.y = self.dataset[self.target_column] # define the target
        
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(self.X, self.y, test_size=self.test_size) # split the data into training and testing
        self.model = RandomForestClassifier() # define the model with random forest classifier
        self.label_encoder = LabelEncoder() # define the label encoder
        self.y_train_encoded = self.label_encoder.fit_transform(self.y_train) # encode the target column
        self.y_test_encoded = self.label_encoder.transform(self.y_test) 
    
    def train(self):
        self.model.fit(self.X_train, self.y_train_encoded)
    
    def predict(self, data: pd.DataFrame):
        return self.model.predict(data)
    
    def evaluate(self):
        return self.model.score(self.X_test, self.y_test_encoded)
    
    def confusion_matrix(self):
        y_pred = self.model.predict(self.X_test)
        return confusion_matrix(self.y_test_encoded, y_pred)
    
    def classification_report(self):
        y_pred = self.model.predict(self.X_test)
        return classification_report(self.y_test_encoded, y_pred)
    
    def roc_curve(self):
        y_pred = self.model.predict_proba(self.X_test)
        fpr, tpr, _ = roc_curve(self.y_test_encoded, y_pred[:, 1])
        plt.plot(fpr, tpr)
        plt.plot([0, 1], [0, 1], linestyle='--')
        plt.xlabel('False Positive Rate')
        plt.ylabel('True Positive Rate')
        plt.title('ROC Curve')
        plt.show()
    
    def feature_importances(self):
        importances = self.model.feature_importances_
        indices = np.argsort(importances)[::-1]
        for f in range(self.X_train.shape[1]):
            print(f'{self.X_train.columns[indices[f]]}: {importances[indices[f]]}')
    
    # plof of an histogram using matplotlib
    def histogram(self, column: str):
        plt.hist(self.dataset[column])
        plt.xlabel(column)
        plt.ylabel('Frequency')
        plt.title(f'Histogram of {column}')
        # plt.show()
        # Format the x-axis labels as integers
        # plt.xticks(np.arange(int(min(self.dataset[column])), int(max(self.dataset[column])) + 1, step=5))

        # plt.tight_layout()  # Adjust layout to prevent overlap
        plt.show()
