import glob
import time
import os

# find all filenames
def locate_files():
  files = []
  for name in glob.glob('cpp_files/*.out'):
    files.append(name)
  return files

def time_execution(filename):
  start = time.time()
  os.system(filename)
  end   = time.time()
  return end-start


if __name__ == "__main__":
  all_files = locate_files()
  print all_files
  f         = open('output.txt', 'w+')
  f.write('\n\n----------------------\n\n')
  for filename in all_files:
    f.write(filename + ':\t' + str(time_execution(filename))+'\n')
  f.close()
