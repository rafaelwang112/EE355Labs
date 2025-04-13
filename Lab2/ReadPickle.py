import pickle

pathName = '/Users/robert/C++/output_py.pickle'
with open(pathName, 'rb') as file:
    data = pickle.load(file)

# Save data to a text file
'''
with open(pathName, 'w') as f:
    f.write(f"Index Row in Matrix 1: {data['idx_row_mat_1']}\n")
    f.write(f"Max Value in Matrix 1: {data['max_mat_1']}\n")
    f.write(f"Min Value in Matrix 1: {data['min_mat_1']}\n")
    f.write(f"Index Row in Matrix 2: {data['idx_row_mat_2']}\n")
    f.write(f"Max Value in Matrix 2: {data['max_mat_2']}\n")
    f.write(f"Min Value in Matrix 2: {data['min_mat_2']}\n\n")

    f.write("Matrix Addition Result:\n")
    for row in data['mat_add']:
        f.write(" ".join(map(str, row)) + "\n")

    f.write("\nMatrix Multiplication Result:\n")
    for row in data['mat_mul']:
        f.write(" ".join(map(str, row)) + "\n")
'''

print(data)