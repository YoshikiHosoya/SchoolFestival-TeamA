xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 70;
 21.99205;0.04925;-14.41937;,
 10.57718;0.04925;-23.87617;,
 21.99205;109.46075;-14.41937;,
 10.57718;109.46075;-23.87617;,
 -4.37313;0.04925;-25.93137;,
 -4.37313;109.46075;-25.93137;,
 -18.11218;0.04925;-19.93236;,
 -18.11218;109.46075;-19.93236;,
 -26.27811;0.04925;-7.78382;,
 -26.27811;109.46075;-7.78382;,
 -26.27811;0.04925;6.65724;,
 -26.27811;109.46075;6.65724;,
 -18.11218;0.04925;18.80580;,
 -18.11218;109.46075;18.80580;,
 -4.37313;0.04925;24.80487;,
 -4.37313;109.46075;24.80487;,
 10.57718;0.04925;22.74967;,
 10.57718;109.46075;22.74967;,
 21.99205;0.04925;13.29277;,
 21.99205;109.46075;13.29280;,
 26.24736;0.04925;-0.56325;,
 26.24736;109.46075;-0.56325;,
 21.99205;0.04925;-14.41937;,
 21.99205;109.46075;-14.41937;,
 10.57718;0.04925;-23.87617;,
 21.99205;0.04925;-14.41937;,
 -0.55826;0.04925;-0.56325;,
 -4.37313;0.04925;-25.93137;,
 -18.11218;0.04925;-19.93236;,
 -26.27811;0.04925;-7.78382;,
 -26.27811;0.04925;6.65724;,
 -18.11218;0.04925;18.80580;,
 -4.37313;0.04925;24.80487;,
 10.57718;0.04925;22.74967;,
 21.99205;0.04925;13.29277;,
 26.24736;0.04925;-0.56325;,
 -0.55826;48.06730;-0.56325;,
 16.23892;48.06730;-10.88435;,
 7.73631;48.06730;-17.92853;,
 -3.39988;48.06715;-19.45942;,
 -13.63383;48.06730;-14.99090;,
 -19.71634;48.06730;-5.94168;,
 -19.71634;48.06730;4.81515;,
 -13.63383;48.06730;13.86429;,
 -3.39988;48.06730;18.33289;,
 7.73631;48.06730;16.80203;,
 16.23892;48.06730;9.75785;,
 19.40861;48.06730;-0.56325;,
 21.99205;109.46075;-14.41937;,
 10.57718;109.46075;-23.87617;,
 16.23892;109.46075;-10.88435;,
 7.73631;109.46075;-17.92853;,
 -4.37313;109.46075;-25.93137;,
 -3.39988;109.46075;-19.45942;,
 -18.11218;109.46075;-19.93236;,
 -13.63383;109.46075;-14.99090;,
 -26.27811;109.46075;-7.78382;,
 -19.71634;109.46075;-5.94168;,
 -26.27811;109.46075;6.65724;,
 -19.71634;109.46075;4.81515;,
 -18.11218;109.46075;18.80580;,
 -13.63383;109.46075;13.86429;,
 -4.37313;109.46075;24.80487;,
 -3.39988;109.46075;18.33289;,
 10.57718;109.46075;22.74967;,
 7.73631;109.46075;16.80203;,
 21.99205;109.46075;13.29280;,
 16.23892;109.46075;9.75785;,
 26.24736;109.46075;-0.56325;,
 19.40861;109.46075;-0.56325;;
 
 88;
 3;0,1,2;,
 3;2,1,3;,
 3;1,4,3;,
 3;3,4,5;,
 3;4,6,5;,
 3;5,6,7;,
 3;6,8,7;,
 3;7,8,9;,
 3;8,10,9;,
 3;9,10,11;,
 3;10,12,11;,
 3;11,12,13;,
 3;12,14,13;,
 3;13,14,15;,
 3;14,16,15;,
 3;15,16,17;,
 3;16,18,17;,
 3;17,18,19;,
 3;18,20,19;,
 3;19,20,21;,
 3;20,22,21;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,24,26;,
 3;28,27,26;,
 3;29,28,26;,
 3;30,29,26;,
 3;31,30,26;,
 3;32,31,26;,
 3;33,32,26;,
 3;34,33,26;,
 3;35,34,26;,
 3;25,35,26;,
 3;36,37,38;,
 3;36,38,39;,
 3;36,39,40;,
 3;36,40,41;,
 3;36,41,42;,
 3;36,42,43;,
 3;36,43,44;,
 3;36,44,45;,
 3;36,45,46;,
 3;36,46,47;,
 3;36,47,37;,
 3;48,49,50;,
 3;50,49,51;,
 3;49,52,51;,
 3;51,52,53;,
 3;52,54,53;,
 3;53,54,55;,
 3;54,56,55;,
 3;55,56,57;,
 3;56,58,57;,
 3;57,58,59;,
 3;58,60,59;,
 3;59,60,61;,
 3;60,62,61;,
 3;61,62,63;,
 3;62,64,63;,
 3;63,64,65;,
 3;64,66,65;,
 3;65,66,67;,
 3;66,68,67;,
 3;67,68,69;,
 3;68,48,69;,
 3;69,48,50;,
 3;63,65,44;,
 3;44,65,45;,
 3;65,67,45;,
 3;45,67,46;,
 3;67,69,46;,
 3;46,69,47;,
 3;69,50,47;,
 3;47,50,37;,
 3;50,51,37;,
 3;37,51,38;,
 3;51,53,38;,
 3;38,53,39;,
 3;53,55,39;,
 3;39,55,40;,
 3;55,57,40;,
 3;40,57,41;,
 3;57,59,41;,
 3;41,59,42;,
 3;59,61,42;,
 3;42,61,43;,
 3;61,63,43;,
 3;43,63,44;;
 
 MeshMaterialList {
  1;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  50;
  0.882741;0.000000;-0.469859;,
  0.487256;0.000000;-0.873259;,
  -0.044053;0.000000;-0.999029;,
  -0.563381;0.000000;-0.826197;,
  -0.922158;0.000000;-0.386812;,
  -0.981119;0.000000;0.193406;,
  -0.711905;0.000000;0.702275;,
  -0.228962;0.000000;0.973435;,
  0.314117;0.000000;0.949384;,
  0.772664;-0.000000;0.634815;,
  0.994801;-0.000000;0.101838;,
  0.772663;0.000000;-0.634817;,
  0.314115;0.000000;-0.949385;,
  -0.228959;0.000000;-0.973436;,
  -0.711904;0.000000;-0.702277;,
  -0.981119;0.000000;-0.193406;,
  -0.922159;0.000000;0.386812;,
  -0.563384;0.000000;0.826195;,
  -0.044054;0.000000;0.999029;,
  0.487258;-0.000000;0.873258;,
  0.882741;-0.000000;0.469859;,
  0.994801;0.000000;-0.101836;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;-0.000001;,
  -0.000006;1.000000;-0.000003;,
  -0.000001;1.000000;-0.000008;,
  0.000005;1.000000;-0.000005;,
  0.228962;0.000000;-0.973435;,
  -0.314116;0.000000;-0.949385;,
  0.044055;0.000000;-0.999029;,
  -0.487258;0.000000;-0.873258;,
  -0.772665;0.000000;-0.634814;,
  -0.882742;0.000000;-0.469858;,
  -0.994801;0.000000;-0.101837;,
  -0.994801;0.000000;0.101837;,
  -0.882742;0.000000;0.469858;,
  -0.772665;0.000000;0.634814;,
  -0.487259;0.000000;0.873257;,
  -0.314118;0.000000;0.949384;,
  0.044051;0.000000;0.999029;,
  0.228957;0.000000;0.973437;,
  0.563383;0.000000;0.826196;,
  0.711909;0.000000;0.702272;,
  0.922161;0.000000;0.386806;,
  0.981119;0.000000;0.193403;,
  0.981119;0.000000;-0.193404;,
  0.922160;0.000000;-0.386808;,
  0.711908;0.000000;-0.702272;,
  0.563385;0.000000;-0.826194;;
  88;
  3;0,1,11;,
  3;11,1,12;,
  3;1,2,12;,
  3;12,2,13;,
  3;2,3,13;,
  3;13,3,14;,
  3;3,4,14;,
  3;14,4,15;,
  3;4,5,15;,
  3;15,5,16;,
  3;5,6,16;,
  3;16,6,17;,
  3;6,7,17;,
  3;17,7,18;,
  3;7,8,18;,
  3;18,8,19;,
  3;8,9,19;,
  3;19,9,20;,
  3;9,10,20;,
  3;20,10,21;,
  3;10,0,21;,
  3;21,0,11;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;24,23,25;,
  3;24,25,26;,
  3;24,26,27;,
  3;24,27,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;24,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;28,29,30;,
  3;30,29,31;,
  3;29,32,31;,
  3;31,32,33;,
  3;32,34,33;,
  3;33,34,35;,
  3;34,36,35;,
  3;35,36,37;,
  3;36,38,37;,
  3;37,38,39;,
  3;38,40,39;,
  3;39,40,41;,
  3;40,42,41;,
  3;41,42,43;,
  3;42,44,43;,
  3;43,44,45;,
  3;44,46,45;,
  3;45,46,47;,
  3;46,48,47;,
  3;47,48,49;,
  3;48,28,49;,
  3;49,28,30;;
 }
 MeshTextureCoords {
  70;
  0.375000;0.312500;,
  0.397730;0.312500;,
  0.375000;0.688440;,
  0.397730;0.688440;,
  0.420460;0.312500;,
  0.420460;0.688440;,
  0.443180;0.312500;,
  0.443180;0.688440;,
  0.465910;0.312500;,
  0.465910;0.688440;,
  0.488640;0.312500;,
  0.488640;0.688440;,
  0.511360;0.312500;,
  0.511360;0.688440;,
  0.534090;0.312500;,
  0.534090;0.688440;,
  0.556820;0.312500;,
  0.556820;0.688440;,
  0.579550;0.312500;,
  0.579550;0.688440;,
  0.602270;0.312500;,
  0.602270;0.688440;,
  0.625000;0.312500;,
  0.625000;0.688440;,
  0.564910;0.014120;,
  0.631450;0.071770;,
  0.500000;0.150000;,
  0.477760;0.001590;,
  0.397680;0.038160;,
  0.350080;0.112230;,
  0.350080;0.200270;,
  0.397680;0.274340;,
  0.477760;0.310910;,
  0.564910;0.298380;,
  0.631450;0.240720;,
  0.656250;0.156250;,
  0.500000;0.837500;,
  0.597910;0.905080;,
  0.548350;0.948020;,
  0.483440;0.957360;,
  0.423780;0.930110;,
  0.388330;0.874950;,
  0.388330;0.809370;,
  0.423780;0.754200;,
  0.483440;0.726950;,
  0.548350;0.736290;,
  0.597910;0.779230;,
  0.616390;0.842150;,
  0.631450;0.928220;,
  0.564910;0.985880;,
  0.597910;0.905080;,
  0.548350;0.948020;,
  0.477760;0.998410;,
  0.483440;0.957360;,
  0.397680;0.961840;,
  0.423780;0.930110;,
  0.350080;0.887770;,
  0.388330;0.874950;,
  0.350080;0.799730;,
  0.388330;0.809370;,
  0.397680;0.725660;,
  0.423780;0.754200;,
  0.477760;0.689090;,
  0.483440;0.726950;,
  0.564910;0.701620;,
  0.548350;0.736290;,
  0.631450;0.759280;,
  0.597910;0.779230;,
  0.656250;0.843750;,
  0.616390;0.842150;;
 }
}
