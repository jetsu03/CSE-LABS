import numpy as np 
import pandas as pd
dataset=pd.read_csv('22.csv')
concepts=np.array(dataset.iloc[:,0:-1])
target=np.array(dataset.iloc[:,-1])
def learn(concepts,target):
    specific_h=concepts[0].copy()
    print('Initial Specific Hypothesis:\n',specific_h)
    general_h=[['?' for i in range(len(specific_h))] for i in range(len(specific_h))]
    print("General Hypothesis:\n",general_h)
    for i,h in enumerate(concepts):
        if target[i]=='yes':
            print("If Instance is Postivie")
            for x in range(len(specific_h)):
                if h[x]!=specific_h[x]:
                    specific_h[x]='?'
                    general_h[x][x]='?'
        if target[i]=='no':
            print("If Instance is Negative")    
            for x in range(len(specific_h)):
                if h[x]!=specific_h[x]:
                    general_h[x][x]=specific_h[x]
                else:
                    general_h[x][x]='?'
        print(" step{}: " .format(i+1))
        print("Specific hypothesis: ",specific_h)
        print("General Hypothesis: ",general_h)  
    indices=[i for i, val in enumerate(general_h) if val==['?','?','?','?','?','?']]
    for i in indices:
        general_h.remove(['?','?','?','?','?','?'])
    return specific_h,general_h
s_final,g_final=learn(concepts,target)
print("Specific Hypothesis: \n",s_final,sep="\n")
print("General Hypothesis: \n",g_final,sep="\n")
