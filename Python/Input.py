import numpy as np
import sys
import configparser
import os
import __main__
import datetime
VERSION="1.0.3"



class Input(object):
    """Parser to read inputfiles and create logs."""
    
    def __init__(self,filename, version, def_opts={}):
        """Create Input parser.
        
        Arguments:
            object {Input} -- the parser object
            filename {str} -- the file with the input options
            version {str} -- version of the program
        
        Keyword Arguments:
            def_opts {dict} -- dictionary with default input options and values. (default: {{}})
        """
        self.filename=filename
        self.version=version
        self.options={}
        self.config = configparser.ConfigParser(def_opts)
        self.config._interpolation = configparser.ExtendedInterpolation()
        self.config.read(filename)
        for sec in self.config:
            self.options[sec]={}
            for key in self.config[sec]:
                self.options[sec][key]=self.config[sec][key]

    def getKeys(self, option, section):
        """Check the existence of the given keys and choose defaults if they are 'None'."""
        if section==None:
            if(len(self.options.keys())>1):
                print("Warning: No section specified, but multiple sections available.")
            section=list(self.options.keys())[0]#possibility to specify standard section
        if option==None:
            option=list(self.options[section].keys())[0]#possibility to specify standard option
        return option, section

    def get(self,  option=None,section=None):
        """Return the specified option.
        
        Keyword Arguments:
            option {string} -- The option to be returned. (default: {First option})
            section {string} -- The section where the option is located. (default: {First section})
        
        Returns:
            value -- value for the given option in the given section 
        """
        option, section=self.getKeys(option, section)
        return self.options[section][option]

    def set(self, value, option=None, section=None):
        """Set an option to a specific value.
        
        Arguments:
            value {obj} -- Value to be placed in the options dictionary.
        
        Keyword Arguments:
            option {str} -- Option to be set. (default: {None})
            section {str} -- Section where the option is located. (default: {None})
        """
        option, section=self.getKeys(option, section)
        self.options[section][option]=value

    def convert_type(self, dtype, option=None, section=None):
        """Convert an input option from string to a given type.
        
        Arguments:
            dtype {type} -- Either int, float, or bool.
        
        Keyword Arguments:
            option {string} -- The option to be converted. (default: {None})
            section {string} -- The section where the option is located (default: {None})
        """
        option, section=self.getKeys(option, section)
        myDict={int: self.config.getint, float: self.config.getfloat, bool: self.config.getboolean}
        self.set(myDict.get(dtype)(section, option),option=option, section=section)

    def convert_array(self, dtype, option=None, section=None, sep=",", removeSpaces=False):
        """Convert an input option from string to an array of the given type.
        
        Arguments:
            dtype {type} -- Type to convert the array element, e.g. str, int, float
        
        Keyword Arguments:
            option {string} -- The option to be converted. (default: {None})
            section {string } -- The section where the option is located (default: {None})
            sep {string} -- The separator between the array values (default: {","})
            removeSpaces {bool} -- Remove spaces in the elements when converting to string array. (default: {False})
        """
        option, section=self.getKeys(option, section)
        if dtype==str:
            array=self.config[section][option].split(sep)
            if removeSpaces:
                array=[x.strip() for x in array]
        else:
            array=np.fromstring(self.config[section][option], sep=sep, dtype=dtype)
        self.set(array, option, section)

    def create_log(self):
        """Create a log of the Input object.
        
        Example:
        Program: Progam1.py
        Version: 1.0.0
        Input options: Config1.ini
        **************************
        ---DEFAULT---
        **************************
        ---Sec1---
        user: 1.0

        Returns:
            array -- array with lines including linebreak. 
        """
        log=[]
        log.append(str(datetime.datetime.now()))
        log.append("BASH: python3 "+" ".join(sys.argv))
        log.append("Program: "+__main__.__file__)
        log.append("Version: "+str(self.version))
        log.append("Input options: "+self.filename)
        for sec in self.options.keys():
            log.append("**************************")
            log.append("---"+str(sec)+"---")
            for opt in self.options[sec].keys():
                log.append(str(opt)+": " + str(self.get(opt,sec)))
        log=[l+"\n" for l in log]        
        return log

    def show_data(self):
        """Print log."""
        print(*self.create_log())                

    def check(self):
        """Perform a consistency check on the input options."""
        everything_ok=True
        #if(something_wrong):
            # everything_oK=False
        return everything_ok

    def write_log(self, new_logs, old_logs=[], file_ext=None):
        """Write log to files.
        
        Combine all old logfiles, append the log of the actual program and save them to all new locations given.

        Arguments:
            old_logs {arr} -- array with old logfiles
            new_logs {arr} -- array with new logfiles to be created.

        Keyword Arguments:
            file_ext {str} -- if set, the file extension in the given logfile locations are replaced before the function is executed. (default: {None})
        """
        old_logs=np.atleast_1d(old_logs)
        new_logs=np.atleast_1d(new_logs)
        if file_ext!=None:
            file_ext=file_ext.strip(".")
            old_logs=[os.path.splitext(logfile)[0]+"."+file_ext for logfile in old_logs]
            new_logs=[os.path.splitext(logfile)[0]+"."+file_ext for logfile in new_logs]

        old_lines=[]
        log=self.create_log()
        for old in old_logs:
            oldfile=open(old)
            old_lines.extend(oldfile.readlines())
            old_lines.append("##############################################################")
            oldfile.close()
        old_lines.append("##############################################################")
        old_lines=[l+"\n" for l in old_lines]
        for new in new_logs:
            newfile=open(new, "w")
            newfile.writelines(old_lines)
            newfile.writelines(log)
            newfile.close()


