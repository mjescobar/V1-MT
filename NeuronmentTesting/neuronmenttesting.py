#!/usr/bin/python

import sys, getopt, os, time

def main(argv):
  testing_source_path = ''
  # Reading Flags
  try:
    opts, args = getopt.getopt(argv,"hp:",["testing_source_path="])
  except getopt.GetoptError:
    print 'neuronmenttesting.py -p <testing_source_path>'
    sys.exit(2)
  for opt, arg in opts:
    if opt == '-h':
      print 'neuronmenttesting.py -p <testing_source_path>'
      sys.exit()
    elif opt in ("-p", "--testing_source_path"):
      testing_source_path = arg
  # Finding main.nproc files on the path
  tests_list = [];
  for root, dirs, files in os.walk(testing_source_path):
    for file in files:
      if file == "main.nproc":
        #tests_list.append(os.path.join(root, file))
        tests_list.append(root)
  print 'Testing source path: '
  print '  ', testing_source_path
  print 'List of detected tests:'
  tests_list.sort()
  for i in tests_list:
    print '  ', i[len(testing_source_path):]
  run_directory = time.strftime('RUN-%Y%m%d-%H%M%S')
  print 'Creating directory to run tests:', os.path.join(os.path.dirname(os.path.realpath("__file__")), run_directory)
  if not os.path.exists(run_directory):
    os.makedirs(run_directory)
    print '  ', 'DONE'
  else:
    print '  ', 'The directory already exists'
    print '  ', 'FAIL'
    sys.exit()
# Main Call
if __name__ == "__main__":
  modified_date = time.strftime('%b %d %Y', time.gmtime(os.path.getmtime(sys.argv[0])))
  print "===================================================================================="
  print "======================= NeuronmentTesting v0.1 - %s =======================" % modified_date
  print "===================================================================================="
  main(sys.argv[1:])
  print "===================================================================================="
  print "Bye!"

