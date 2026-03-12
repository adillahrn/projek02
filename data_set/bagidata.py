import csv

input_file = "trans20k.csv"

sizes = [1000, 10000, 20000]

with open(input_file, 'r') as f:
    rows = f.readlines()

header = rows[0]
data = rows[1:]

for size in sizes:
    with open(f"trans{size}.csv", "w") as out:
        out.write(header)
        out.writelines(data[:size])