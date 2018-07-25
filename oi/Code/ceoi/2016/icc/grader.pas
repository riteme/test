program grader;

uses icc;

{$L graderlib.o}
{$LINKLIB c}
{$LINKLIB m}
{$LINKLIB stdc++}

procedure InitGrader(); cdecl; external;
function NumVertices(): LongInt; cdecl; external;
procedure GraderExitFail(); cdecl; external;

begin
    InitGrader();
    run(NumVertices());
    GraderExitFail();
end.
