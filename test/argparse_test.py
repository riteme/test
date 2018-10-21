#!/usr/bin/env python

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('echo', help='Your text')
args = parser.parse_args()
print args.echo
