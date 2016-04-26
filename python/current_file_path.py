
import os

file_path = os.path.abspath(__file__)

joined_path = os.path.join(file_path, '../..')

print os.path.normpath(joined_path)
