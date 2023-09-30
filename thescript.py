import pandas as pd
import matplotlib.pyplot as plt
import csv
import numpy as np




# # for question 1
# df = pd.read_csv("traces.csv",header=None)
# print("printing the power trace of trace1")
# for i in range(0,1):
#     plt.plot(df.loc[i,0:400],)

# plt.xlabel("Column Number")
# plt.ylabel("Value")
# plt.title("Values in Each Column")
# plt.legend()
# plt.show()




# # question 2 give the trace for the 0x00 and 0xff
# df = pd.read_csv("correlation_256x400_for_1st_byte.csv",header=None)
# for i in range(0,256):
#     if(i == 0):
#         plt.plot(df.loc[i,0:400],'-', label= '0x00')
#     if(i == 255):
#         plt.plot(df.loc[i,0:400],'-', label = '0xff')
# # plt.plot(df.loc[1000,0:200],'o-')

# plt.xlabel("timestamps")
# plt.ylabel("Pearson Coefficient")
# plt.title("for Keys 0x00 and 0xff")
# plt.legend()
# plt.show()












# # question this will print all the correlation and tells the most likely key

# def process_csv_file(filename, output_file):
#     # Initialize variables for the minimum and maximum values
#     min_values = [float('inf')] * 2  # List to store the two smallest values, initialized with positive infinity
#     max_values = [float('-inf')] * 2  # List to store the two largest values, initialized with negative infinity
#     key_row_min = [None] * 2
#     key_row_max = [None] * 2
#     time_stamp_min = [None] * 2
#     time_stamp_max = [None] * 2

#     # Open the CSV file for reading
#     with open(filename, 'r') as csvfile:
#         reader = csv.reader(csvfile)

#         # Iterate through the rows and columns
#         for row_value, row in enumerate(reader):
#             for col_value, cell in enumerate(row):
#                 try:
#                     # Attempt to convert the cell value to a floating-point number
#                     value = float(cell)

#                     # Update lists for the two smallest values
#                     if value < min_values[0]:
#                         min_values[1] = min_values[0]
#                         key_row_min[1] = key_row_min[0]
#                         time_stamp_min[1] = time_stamp_min[0]

#                         min_values[0] = value
#                         key_row_min[0] = row_value
#                         time_stamp_min[0] = col_value
#                     elif value < min_values[1]:
#                         min_values[1] = value
#                         key_row_min[1] = row_value
#                         time_stamp_min[1] = col_value

#                     # Update lists for the two largest values
#                     if value > max_values[0]:
#                         max_values[1] = max_values[0]
#                         key_row_max[1] = key_row_max[0]
#                         time_stamp_max[1] = time_stamp_max[0]

#                         max_values[0] = value
#                         key_row_max[0] = row_value
#                         time_stamp_max[0] = col_value
#                     elif value > max_values[1]:
#                         max_values[1] = value
#                         key_row_max[1] = row_value
#                         time_stamp_max[1] = col_value

#                 except ValueError:
#                     # Ignore non-numeric values in the CSV
#                     pass

#     # Display the results and write to the output file
#     with open(output_file, 'a') as outputfile:
#         outputfile.write(f"For file {filename}:\n")
#         for i in range(2):
#             if(i == 0):
#                 outputfile.write(f"  {i + 1}. The smallest pearson coefficient is: {min_values[i]}, the key is 0x{key_row_min[i]:x}, the time stamp is {time_stamp_min[i]}\n")
#                 outputfile.write(f"  {i + 1}. The largest pearson coefficient is: {max_values[i]}, the key is 0x{key_row_max[i]:x}, the time stamp is {time_stamp_max[i]}\n")

#             if(i == 1):
#                 outputfile.write(f"  {i + 1}. The previous smallest pearson coefficient is: {min_values[i]}, the key is 0x{key_row_min[i]:x}, the time stamp is {time_stamp_min[i]}\n")
#                 outputfile.write(f"  {i + 1}. The previous largest pearson coefficient is: {max_values[i]}, the key is 0x{key_row_max[i]:x}, the time stamp is {time_stamp_max[i]}\n")

# # List of filenames to process
# filenames = ["correlation_256x400_for_1st_byte.csv", "correlation_256x400_for_2nd_byte.csv",
#              "correlation_256x400_for_3rd_byte.csv",
#         "correlation_256x400_for_4th_byte.csv",
#         "correlation_256x400_for_5th_byte.csv",
#         "correlation_256x400_for_6th_byte.csv",
#         "correlation_256x400_for_7th_byte.csv",
#         "correlation_256x400_for_8th_byte.csv",
#         "correlation_256x400_for_9th_byte.csv",
#         "correlation_256x400_for_10th_byte.csv",
#         "correlation_256x400_for_11th_byte.csv",
#         "correlation_256x400_for_12th_byte.csv",
#         "correlation_256x400_for_13th_byte.csv",
#         "correlation_256x400_for_14th_byte.csv",
#         "correlation_256x400_for_15th_byte.csv",
#         "correlation_256x400_for_16th_byte.csv"
        
#             ]
# output_file = "print_key_set_and_timestamps.txt"

# # Process each CSV file and append the results to the output file
# for filename in filenames:
#     process_csv_file(filename, output_file)

# print("Find the output at print_key_set_and_timestamps.txt")



#this part of code will give the trace measurements

def find_max_value_timestamp_for_evolution(filename_evolution, output_file, byte_to_check):
    # Load the CSV file into a DataFrame
    df = pd.read_csv(filename_evolution, header=None)

    # Extract the first row as a 1D NumPy array
    first_row_array = np.array(df.iloc[byte_to_check])
    first_row_array = first_row_array[1000:]

    # Print the first row as a NumPy array
    max_value = 0
    index_v = 0
    for row_value, r in enumerate(first_row_array):
        if abs(r) > abs(max_value):
            max_value = r
            index_v = row_value+1
    mean_of_all = index_v+1000
    with open(output_file, 'a') as output_file_obj:
        output_file_obj.write(f"The index value for the file {filename_evolution} is {mean_of_all}\n")
        output_file_obj.write(f"the key is 0x{byte_to_check:x}\n")
        output_file_obj.write(f"Max value: {max_value}\n")
    return mean_of_all

# List of filenames to process
filenames = ["evolution_of_the_1st_byte.csv",
             "evolution_of_the_2nd_byte.csv",
             "evolution_of_the_3rd_byte.csv",
             "evolution_of_the_4th_byte.csv",
            "evolution_of_the_5th_byte.csv",
            "evolution_of_the_6th_byte.csv",
            "evolution_of_the_7th_byte.csv",
            "evolution_of_the_8th_byte.csv",
            "evolution_of_the_9th_byte.csv",
            "evolution_of_the_10th_byte.csv",
            "evolution_of_the_11th_byte.csv",
            "evolution_of_the_12th_byte.csv",
            "evolution_of_the_13th_byte.csv",
            "evolution_of_the_14th_byte.csv",
            "evolution_of_the_15th_byte.csv",
            "evolution_of_the_16th_byte.csv"
            ]
output_file = "trace_value_from_evolution.txt"
mean_Value = 0
with open(output_file, 'w') as clear_file:
    clear_file.write("")
# Process each CSV file and append the results to the output file
byte_to_check = 0
for filename in filenames:
    # Clear the output file by opening it in 'w' (write) mode
    mean_Value += find_max_value_timestamp_for_evolution(filename, output_file, byte_to_check)
    byte_to_check+=1
with open(output_file, 'a') as output_file_obj:
    output_file_obj.write(f"the mean value is: {mean_Value/16}")

print("Find the output at trace_value_from_evolution.txt")
