#!/usr/bin/python

import sys, getopt, os, time, errno, shutil

def main(argv):
  current_path = os.path.dirname(os.path.realpath("__file__"))
  testing_source_path = ''
  executable_path = ''
  # Reading Flags
  try:
    opts, args = getopt.getopt(argv,"he:p:",["testing_source_path=", "executable_path="])
  except getopt.GetoptError:
    print 'neuronmenttesting.py -e <executable_to_use> -p <testing_source_path>'
    sys.exit(2)
  for opt, arg in opts:
    if opt == '-h':
      print 'neuronmenttesting.py -e <executable_to_use> -p <testing_source_path>'
      sys.exit()
    elif opt in ("-p", "--testing_source_path"):
      testing_source_path = arg
    elif opt in ("-e", "--executable_path"):
      executable_path = arg
  # Finding main.nproc files on the path
  tests_list = [];
  for root, dirs, files in os.walk(testing_source_path):
    for file in files:
      if file == "main.nproc":
        #tests_list.append(os.path.join(root, file))
        tests_list.append(root)
  print 'Testing source path: '
  print '  ', testing_source_path
  if len(tests_list) == 0:
    print '  ', 'FAIL - No tests found on the chosen path'
    return
  print 'List of detected tests:'
  tests_list.sort()
  for i in tests_list:
    print '  ', i[len(testing_source_path):]
  run_directory = time.strftime('RUN-%Y%m%d-%H%M%S')
  print 'Directory to run tests:'
  print '  ', os.path.join(current_path, run_directory)
  print 'Copying test files to test directory:'
  result = foldercopy(testing_source_path, run_directory)
  print '  ', result
  if result.startswith('FAIL'):
    return
  # Creating list of tests in test folder
  print 'Finding the tests on the RUN folder:'
  tests_list = []
  for root, dirs, files in os.walk(run_directory):
    for file in files:
      if file == "main.nproc":
        tests_list.append(root)
  print '  ', 'DONE'
  # Copying executable to folder
  print 'Copying executable file:', executable_path
  result = execcopy(executable_path, run_directory)
  print '  ', result
  if result.startswith('FAIL'):
    return
  # Creating symbolic links to executable on test folders
  print 'Creating symbolic links to the executable:'
  os.chmod(current_path + "/" + run_directory + "/neuronment", 0755)
  for i in tests_list:
    try:
      os.symlink(current_path + "/" + run_directory + "/neuronment", i + "/neuronment")
    except OSError as e:
      return '  ','FAIL - Error: %s' % e
  print '  ', 'DONE'
  # Running tests
  print 'Running tests:'
  for i in tests_list:
    try:
      os.chdir(current_path + "/" + i)
    except OSError as e:
      print '  ', 'FAIL - Error: %s' % e
      return
    if os.path.isfile('main.customrun'):
      os.chmod("main.run", 0755)
      os.system("./main.customrun > main.result")
    else:
      os.system('./neuronment -nproc main.nproc > main.result 2> main.error')
      result = evaluate_result(current_path + "/" + i);
      print '  ', '[%s] %s' % (result, i);

def evaluate_result(test_folder):
  if os.stat(test_folder + "/" + 'main.error').st_size > 0:
    return 'ASRT'
  else:
    return 'DONE'

def foldercopy(src, dest):
  try:
    shutil.copytree(src, dest)
    return 'DONE'
  except OSError as e:
    if e.errno == errno.ENOTDIR:
      return 'FAIL - You should specify the folder containing the test'
    else:
      return 'FAIL - Error: %s' % e

def execcopy(src, dest):
  try:
    shutil.copyfile(src, dest + "/neuronment")
    return 'DONE'
  except OSError as e:
    return 'FAIL - Error: %s' % e

# Main Call
if __name__ == "__main__":
  modified_date = time.strftime('%b %d %Y', time.gmtime(os.path.getmtime(sys.argv[0])))
  print "===================================================================================="
  print "======================= NeuronmentTesting v0.1 - %s =======================" % modified_date
  print "===================================================================================="
  main(sys.argv[1:])
  print "===================================================================================="
  print "Bye!"

