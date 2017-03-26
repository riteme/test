unit graderhelplib;

interface

procedure setRoad(A, B: LongInt); cdecl; external;

function query(sizeA, sizeB: LongInt; var A, B: array of LongInt) : LongInt; cdecl; external;

implementation

end.
