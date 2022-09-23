import os
import argparse
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument('-f', '--folder', type=str, default='data')
parser.add_argument('-o', '--output', type=str, default='output.bundle')
args = parser.parse_args()

files = sorted(filter(lambda name: name.endswith('.ts'), os.listdir(args.folder)))

with open(args.output, 'wb') as fout:
    for name in files:
        path = f'{args.folder}/{name}'
        p = subprocess.run([
            'ffprobe',
            '-v', 'error',
            '-of', 'csv=p=0',
            '-show_entries', 'format=duration',
            '-i', path
        ], stdout=subprocess.PIPE)
        duration = int(p.stdout.decode('utf-8').replace('.', ''))
        print(f'{path}: {duration} us')
        with open(path, 'rb') as fin:
            data = fin.read()
            fout.write(len(data).to_bytes(8, 'little'))
            fout.write(duration.to_bytes(8, 'little'))
            fout.write(data)
    fout.write(int(0).to_bytes(8, 'little'))
