import os

def A(x):
    n = 0
    for i in range(1, x + 1):
        if  x % i == 0:
            n += 1

    return n

def generete_point(x, y):
    return """<element type="point" label="{x}">
<show object="true" label="false"/>
<objColor r="0" g="0" b="255" alpha="0.0"/>
<layer val="0"/>
<labelMode val="0"/>
<animation step="1" speed="1" type="1" playing="false"/>
<coords x="{x}.0" y="{y}.0" z="1.0"/>
<pointSize val="5"/>
<pointStyle val="0"/>
</element>""".format(x=x, y=y)

N = 1000

with open("graph.dat", "w") as writer:
    prefix = 0
    for i in range(1, N + 1):
        prefix += A(i)
        writer.write(
            generete_point(i, prefix)
        ) 
