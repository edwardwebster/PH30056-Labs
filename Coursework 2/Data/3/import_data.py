import pandas as pd
import numpy as np

def import_data(filename):
    output = pd.DataFrame({}, columns=[
        "temperature", "magnetisation", "energy",
        "unc_mag", "unc_energy",
        "var_mag", "var_energy",
        "av_cor1", "av_cor2", "av_cor3"
    ])

    input = pd.read_csv(filename, sep=',', header=0, skiprows=2)

    for beta in input['beta'].unique():
        sample_filter = input['beta'] == beta
        sample = input[sample_filter]

        output = output.append({
            "temperature": 1/beta,

            "magnetisation": np.mean(sample['magnetisation']),
            "unc_mag": np.std(sample['magnetisation'][0:-1:10]),

            "energy": np.mean(sample['energy']),
            "unc_energy": np.std(sample['energy'][0:-1:10]),

            "var_mag": np.var(sample['magnetisation']),
            "var_energy":np.var(sample['energy']),

            "av_cor1": np.mean(sample['cor1'][0:-1:1]),
            "av_cor2":np.mean(sample['cor2'][0:-1:1]),
            "av_cor3":np.mean(sample['cor3'][0:-1:1]),

            "unc_av_cor1": np.std(sample['cor1'][0:-1:1]),
            "unc_av_cor2":np.std(sample['cor2'][0:-1:1]),
            "unc_av_cor3":np.std(sample['cor3'][0:-1:1])

        },ignore_index=True)

    output = output.dropna(0)
    return output
