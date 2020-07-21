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
 142;
 -1.31158;1.54484;3.15006;,
 -1.14748;0.37436;2.84635;,
 0.07634;1.54484;3.15006;,
 0.06374;0.37436;2.84635;,
 -2.98716;2.60336;-1.59969;,
 -3.66923;0.22280;-1.59969;,
 -2.98716;2.60336;0.11147;,
 -3.66923;0.22280;0.11147;,
 0.06374;0.37436;-2.94845;,
 -1.14748;0.37436;-2.94845;,
 0.07634;1.54484;-3.25216;,
 -1.31158;1.54484;-3.25216;,
 2.94202;2.60336;0.11147;,
 3.62409;0.22280;0.11147;,
 2.94202;2.60336;-1.59969;,
 3.62409;0.22280;-1.59969;,
 -1.31158;2.60336;-1.59969;,
 -1.31158;2.60336;0.11147;,
 0.07634;2.60336;-1.59969;,
 0.07634;2.60336;0.11147;,
 -0.82310;-9.37840;-1.38629;,
 0.03635;-9.40137;-1.35044;,
 -0.79061;-9.40137;0.33581;,
 0.03635;-9.40137;0.33581;,
 3.15986;-2.33755;0.21141;,
 3.15986;-2.33755;-1.50635;,
 0.06374;-2.33755;-2.94845;,
 -1.14748;-2.33755;-2.94845;,
 -3.20500;-2.33755;-1.50635;,
 -3.20500;-2.33755;0.21141;,
 -1.14748;-2.33755;2.84635;,
 0.06374;-2.33755;2.84635;,
 2.81777;-5.12863;0.21141;,
 2.81777;-5.12863;-1.50635;,
 0.05447;-5.12863;-2.94845;,
 -1.02657;-5.12863;-2.94845;,
 -2.86291;-5.12863;-1.50635;,
 -2.86291;-5.12863;0.21141;,
 -1.02657;-5.12863;2.84635;,
 0.05447;-5.12863;2.84635;,
 2.15034;-8.11625;0.33581;,
 2.15034;-8.11625;-1.35044;,
 0.05447;-7.91887;-2.94845;,
 -1.02657;-7.91887;-2.94845;,
 -2.19548;-8.11625;-1.35044;,
 -2.19548;-8.11625;0.33581;,
 -1.02657;-7.91887;2.84635;,
 0.05447;-7.91887;2.84635;,
 1.74388;-9.40137;-1.35044;,
 1.74388;-9.40137;0.33581;,
 -0.82310;-8.71759;-2.41787;,
 0.03635;-8.69467;-2.45366;,
 -1.78902;-9.40137;0.33581;,
 -1.75659;-9.37840;-1.38629;,
 0.03635;-8.69467;2.35156;,
 -0.79061;-8.69467;2.35156;,
 -1.78902;-9.40137;1.57035;,
 -2.19548;-8.11625;1.57035;,
 -2.86291;-5.12863;1.82514;,
 -3.20500;-2.33755;1.82514;,
 -3.66923;0.22280;1.97992;,
 -2.98716;2.60336;1.97992;,
 -1.31158;2.60336;1.97992;,
 0.07634;2.60336;1.97992;,
 2.94202;2.60336;1.97992;,
 3.62409;0.22280;1.97992;,
 3.15986;-2.33755;1.82514;,
 2.81777;-5.12863;1.82514;,
 2.15034;-8.11625;1.57035;,
 1.74388;-9.40137;1.57035;,
 -0.79061;-9.40137;1.57035;,
 0.03635;-9.40137;1.57035;,
 1.74388;-8.69467;-2.45366;,
 1.74388;-8.11625;-2.45366;,
 2.28651;-5.12863;-2.94845;,
 2.56457;-2.33755;-2.94845;,
 2.94202;0.22280;-3.25216;,
 2.94202;1.54484;-3.25216;,
 -1.31158;1.54484;-3.25216;,
 0.07634;1.54484;-3.25216;,
 -2.98716;0.22280;-3.25216;,
 -2.98716;1.54484;-3.25216;,
 -2.60971;-2.33755;-2.94845;,
 -2.33165;-5.12863;-2.94845;,
 -1.78902;-8.11625;-2.45366;,
 -1.75659;-8.71759;-2.41787;,
 0.03635;-8.69467;-2.45366;,
 -0.82310;-8.71759;-2.41787;,
 -1.78902;-8.69467;2.35156;,
 -1.78902;-8.11625;2.35156;,
 -2.33165;-5.12863;2.84635;,
 -2.60971;-2.33755;2.84635;,
 -2.98716;0.22280;3.15006;,
 -2.98716;1.54484;3.15006;,
 2.94202;0.22280;3.15006;,
 2.94202;1.54484;3.15006;,
 2.56457;-2.33755;2.84635;,
 2.28651;-5.12863;2.84635;,
 1.74388;-8.11625;2.35156;,
 1.74388;-8.69467;2.35156;,
 1.03116;-7.91887;2.84635;,
 0.78355;-8.69467;2.35156;,
 1.03116;-5.12863;2.84635;,
 1.15806;-2.33755;2.84635;,
 1.15806;0.37436;2.84635;,
 1.33027;1.54484;3.15006;,
 1.33027;2.60336;1.97992;,
 1.33027;2.60336;0.11147;,
 1.33027;2.60336;-1.59969;,
 1.33027;1.54484;-3.25216;,
 1.33027;1.54484;-3.25216;,
 1.15806;0.37436;-2.94845;,
 1.15806;-2.33755;-2.94845;,
 1.03116;-5.12863;-2.94845;,
 1.03116;-7.91887;-2.94845;,
 0.78355;-8.69467;-2.45366;,
 0.78355;-8.69467;-2.45366;,
 0.78355;-9.40137;-1.35044;,
 0.78355;-9.40137;0.33581;,
 0.78355;-9.40137;1.57035;,
 -2.98716;2.60336;-1.59969;,
 -2.98716;1.54484;-3.25216;,
 -2.98716;2.60336;0.11147;,
 -2.98716;2.60336;1.97992;,
 -1.78902;-9.40137;1.57035;,
 -1.78902;-9.40137;0.33581;,
 -1.75659;-9.37840;-1.38629;,
 -1.75659;-8.71759;-2.41787;,
 1.74388;-8.11625;2.35156;,
 1.74388;-8.69467;2.35156;,
 2.28651;-5.12863;2.84635;,
 2.56457;-2.33755;2.84635;,
 2.94202;0.22280;3.15006;,
 2.94202;1.54484;3.15006;,
 2.94202;2.60336;1.97992;,
 2.94202;2.60336;0.11147;,
 2.94202;2.60336;-1.59969;,
 2.94202;1.54484;-3.25216;,
 1.74388;-8.69467;-2.45366;,
 1.74388;-9.40137;-1.35044;,
 1.74388;-9.40137;0.33581;,
 1.74388;-9.40137;1.57035;;
 
 224;
 3;0,1,2;,
 3;2,1,3;,
 3;4,5,6;,
 3;6,5,7;,
 3;8,9,10;,
 3;10,9,11;,
 3;12,13,14;,
 3;14,13,15;,
 3;16,17,18;,
 3;18,17,19;,
 3;20,21,22;,
 3;22,21,23;,
 3;24,25,13;,
 3;13,25,15;,
 3;8,26,9;,
 3;9,26,27;,
 3;5,28,7;,
 3;7,28,29;,
 3;1,30,3;,
 3;3,30,31;,
 3;24,32,25;,
 3;25,32,33;,
 3;34,35,26;,
 3;26,35,27;,
 3;28,36,29;,
 3;29,36,37;,
 3;30,38,31;,
 3;31,38,39;,
 3;40,41,32;,
 3;32,41,33;,
 3;34,42,35;,
 3;35,42,43;,
 3;36,44,37;,
 3;37,44,45;,
 3;38,46,39;,
 3;39,46,47;,
 3;48,41,49;,
 3;49,41,40;,
 3;43,42,50;,
 3;50,42,51;,
 3;45,44,52;,
 3;52,44,53;,
 3;54,47,55;,
 3;55,47,46;,
 3;56,57,52;,
 3;52,57,45;,
 3;45,57,37;,
 3;37,57,58;,
 3;29,37,59;,
 3;59,37,58;,
 3;29,59,7;,
 3;7,59,60;,
 3;6,7,61;,
 3;61,7,60;,
 3;17,62,19;,
 3;19,62,63;,
 3;64,65,12;,
 3;12,65,13;,
 3;65,66,13;,
 3;13,66,24;,
 3;66,67,24;,
 3;24,67,32;,
 3;67,68,32;,
 3;32,68,40;,
 3;49,40,69;,
 3;69,40,68;,
 3;70,22,71;,
 3;71,22,23;,
 3;72,73,48;,
 3;48,73,41;,
 3;41,73,33;,
 3;33,73,74;,
 3;25,33,75;,
 3;75,33,74;,
 3;25,75,15;,
 3;15,75,76;,
 3;15,76,14;,
 3;14,76,77;,
 3;78,16,79;,
 3;79,16,18;,
 3;5,4,80;,
 3;80,4,81;,
 3;28,5,82;,
 3;82,5,80;,
 3;83,36,82;,
 3;82,36,28;,
 3;44,36,84;,
 3;84,36,83;,
 3;44,84,53;,
 3;53,84,85;,
 3;86,21,87;,
 3;87,21,20;,
 3;88,89,56;,
 3;56,89,57;,
 3;57,89,58;,
 3;58,89,90;,
 3;59,58,91;,
 3;91,58,90;,
 3;59,91,60;,
 3;60,91,92;,
 3;60,92,61;,
 3;61,92,93;,
 3;2,63,0;,
 3;0,63,62;,
 3;65,64,94;,
 3;94,64,95;,
 3;66,65,96;,
 3;96,65,94;,
 3;97,67,96;,
 3;96,67,66;,
 3;68,67,98;,
 3;98,67,97;,
 3;68,98,69;,
 3;69,98,99;,
 3;55,70,54;,
 3;54,70,71;,
 3;100,47,101;,
 3;101,47,54;,
 3;39,47,102;,
 3;102,47,100;,
 3;39,102,31;,
 3;31,102,103;,
 3;3,31,104;,
 3;104,31,103;,
 3;3,104,2;,
 3;2,104,105;,
 3;105,106,2;,
 3;2,106,63;,
 3;19,63,107;,
 3;107,63,106;,
 3;18,19,108;,
 3;108,19,107;,
 3;79,18,109;,
 3;109,18,108;,
 3;110,111,10;,
 3;10,111,8;,
 3;111,112,8;,
 3;8,112,26;,
 3;112,113,26;,
 3;26,113,34;,
 3;113,114,34;,
 3;34,114,42;,
 3;51,42,115;,
 3;115,42,114;,
 3;116,117,86;,
 3;86,117,21;,
 3;23,21,118;,
 3;118,21,117;,
 3;71,23,119;,
 3;119,23,118;,
 3;54,71,101;,
 3;101,71,119;,
 3;85,84,50;,
 3;50,84,43;,
 3;43,84,35;,
 3;35,84,83;,
 3;35,83,27;,
 3;27,83,82;,
 3;27,82,9;,
 3;9,82,80;,
 3;9,80,11;,
 3;11,80,81;,
 3;120,16,121;,
 3;121,16,78;,
 3;122,17,120;,
 3;120,17,16;,
 3;123,62,122;,
 3;122,62,17;,
 3;0,62,93;,
 3;93,62,123;,
 3;1,0,92;,
 3;92,0,93;,
 3;30,1,91;,
 3;91,1,92;,
 3;38,30,90;,
 3;90,30,91;,
 3;46,38,89;,
 3;89,38,90;,
 3;55,46,88;,
 3;88,46,89;,
 3;124,70,88;,
 3;88,70,55;,
 3;125,22,124;,
 3;124,22,70;,
 3;126,20,125;,
 3;125,20,22;,
 3;87,20,127;,
 3;127,20,126;,
 3;128,100,129;,
 3;129,100,101;,
 3;100,128,102;,
 3;102,128,130;,
 3;102,130,103;,
 3;103,130,131;,
 3;103,131,104;,
 3;104,131,132;,
 3;104,132,105;,
 3;105,132,133;,
 3;133,134,105;,
 3;105,134,106;,
 3;107,106,135;,
 3;135,106,134;,
 3;108,107,136;,
 3;136,107,135;,
 3;109,108,137;,
 3;137,108,136;,
 3;111,110,76;,
 3;76,110,77;,
 3;112,111,75;,
 3;75,111,76;,
 3;113,112,74;,
 3;74,112,75;,
 3;114,113,73;,
 3;73,113,74;,
 3;115,114,72;,
 3;72,114,73;,
 3;138,139,116;,
 3;116,139,117;,
 3;118,117,140;,
 3;140,117,139;,
 3;119,118,141;,
 3;141,118,140;,
 3;101,119,129;,
 3;129,119,141;;
 
 MeshMaterialList {
  2;
  224;
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
   0.693600;0.508000;0.360800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  139;
  0.886079;0.000000;0.463535;,
  1.000000;0.000000;0.000000;,
  -0.878739;0.000000;0.477303;,
  -1.000000;0.000000;0.000000;,
  -0.997791;-0.055935;-0.035830;,
  -1.000000;0.000000;0.000000;,
  0.886079;0.000000;-0.463535;,
  1.000000;0.000000;0.000000;,
  0.938887;0.019692;0.343661;,
  0.966170;0.026682;-0.256521;,
  -0.966170;0.026682;-0.256521;,
  -0.938887;0.019692;0.343661;,
  0.861343;-0.140455;0.488221;,
  0.918751;-0.140837;-0.368865;,
  -0.918751;-0.140837;-0.368865;,
  -0.861344;-0.140455;0.488221;,
  0.875706;-0.160003;0.455563;,
  0.926584;-0.157874;-0.341346;,
  -0.926584;-0.157874;-0.341346;,
  -0.875707;-0.160003;0.455562;,
  0.757251;-0.143685;0.637122;,
  0.871002;-0.130293;-0.473686;,
  -0.760638;-0.255359;-0.596843;,
  -0.832461;-0.130578;0.538478;,
  -0.951319;-0.308157;-0.005540;,
  -0.965599;-0.260035;0.000000;,
  -0.984223;-0.176929;0.000000;,
  -0.989518;-0.144413;0.000000;,
  -0.999864;0.016520;0.000000;,
  -0.961320;0.275434;0.000000;,
  0.961320;0.275434;0.000000;,
  0.999864;0.016520;0.000000;,
  0.989518;-0.144412;-0.000000;,
  0.984223;-0.176930;-0.000000;,
  0.963311;-0.268386;-0.000000;,
  0.953447;-0.301560;-0.000000;,
  0.973265;-0.199932;-0.113062;,
  0.958657;-0.261183;-0.112964;,
  0.957037;-0.167543;-0.236665;,
  0.980201;-0.151121;-0.127940;,
  0.972303;-0.000866;-0.233722;,
  0.974025;0.205945;-0.094135;,
  -0.975276;0.181553;-0.125995;,
  -0.979623;0.047295;-0.195195;,
  -0.975591;-0.156803;-0.153734;,
  -0.965741;-0.161492;-0.203138;,
  -0.956222;-0.268501;-0.116390;,
  -0.963568;-0.232821;-0.131648;,
  -0.968312;-0.197178;0.153272;,
  -0.952599;-0.263164;0.152640;,
  -0.932369;-0.170654;0.318692;,
  -0.973301;-0.152891;0.171201;,
  -0.949629;-0.006460;0.313310;,
  -0.970767;0.204192;0.126166;,
  0.969274;0.178528;0.169222;,
  0.964115;0.043381;0.261917;,
  0.965596;-0.158767;0.205954;,
  0.947572;-0.164592;0.273892;,
  0.949507;-0.254471;0.183526;,
  0.967699;-0.224689;0.114343;,
  0.000000;-0.665754;0.746171;,
  0.000000;-0.319802;0.947484;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.101247;0.994861;,
  0.000000;-0.251163;0.967945;,
  0.000000;0.933165;0.359449;,
  0.000000;1.000000;0.000000;,
  0.000000;0.959702;-0.281021;,
  0.000000;-0.251163;-0.967945;,
  0.000000;-0.101247;-0.994861;,
  0.000000;0.000000;-1.000000;,
  -0.003092;-0.322278;-0.946640;,
  -0.004253;-0.736796;-0.676102;,
  -0.003896;-0.970149;-0.242480;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.933162;0.359456;,
  -0.053577;-0.644438;-0.762778;,
  -0.236851;-0.305726;-0.922190;,
  -0.079481;-0.023855;-0.996551;,
  0.049939;-0.117943;-0.991764;,
  0.059489;-0.159965;-0.985328;,
  0.000000;0.927863;-0.372922;,
  0.000000;0.951505;0.307634;,
  0.059489;-0.159966;0.985328;,
  0.058262;-0.137600;0.988773;,
  -0.093005;-0.027915;0.995274;,
  -0.195184;-0.192802;0.961629;,
  0.000000;-0.624629;0.780922;,
  0.000000;-0.879785;0.475372;,
  -0.003741;-0.999986;-0.003741;,
  -0.004542;-0.957814;-0.287354;,
  0.000000;-0.645426;0.763823;,
  0.247716;-0.233577;0.940255;,
  0.083448;-0.023909;0.996225;,
  -0.051439;-0.117534;0.991736;,
  -0.041450;0.230153;0.972271;,
  0.000000;0.959702;-0.281021;,
  0.000000;0.694348;-0.719639;,
  -0.060013;-0.137125;-0.988734;,
  0.097679;-0.027986;-0.994824;,
  0.205320;-0.193602;-0.959355;,
  0.000000;-0.706402;-0.707811;,
  0.000000;-0.959700;-0.281026;,
  0.000000;-0.933162;0.359456;,
  0.000000;0.842055;-0.539392;,
  0.000000;0.842055;-0.539392;,
  0.000000;0.741592;0.670851;,
  0.000000;0.741592;0.670851;,
  0.000000;0.741592;0.670851;,
  -0.091358;-0.237498;-0.967082;,
  0.000000;-0.642933;-0.765922;,
  0.000000;-0.059408;-0.998234;,
  0.000000;-0.054626;-0.998507;,
  0.056747;-0.030597;-0.997920;,
  0.116303;-0.105932;-0.987548;,
  0.000000;0.629488;-0.777010;,
  0.000000;0.982462;-0.186461;,
  0.000000;0.933165;0.359449;,
  0.000000;0.535080;0.844802;,
  0.116304;-0.105933;0.987548;,
  0.056747;-0.030597;0.997920;,
  0.000000;-0.054626;0.998507;,
  0.000000;-0.163386;0.986562;,
  0.000000;-0.679025;0.734115;,
  0.000000;-0.971342;0.237686;,
  0.000000;-0.999960;-0.008894;,
  0.000000;-0.957805;-0.287420;,
  0.000000;-0.054626;0.998507;,
  -0.058460;-0.030320;0.997829;,
  -0.119792;-0.104948;0.987236;,
  0.000000;0.405678;0.914016;,
  0.000000;0.879790;0.475363;,
  -0.119792;-0.104948;-0.987236;,
  -0.058460;-0.030320;-0.997829;,
  0.000000;-0.054626;-0.998507;,
  0.000000;-0.163387;-0.986562;,
  0.000000;-0.706402;-0.707811;,
  0.000000;-0.927860;-0.372929;,
  -0.000000;-0.971342;0.237686;;
  224;
  3;83,84,64;,
  3;64,84,63;,
  3;42,43,29;,
  3;29,43,28;,
  3;69,79,68;,
  3;68,79,80;,
  3;30,31,41;,
  3;41,31,40;,
  3;81,66,67;,
  3;67,66,66;,
  3;90,73,89;,
  3;89,73,74;,
  3;32,39,31;,
  3;31,39,40;,
  3;69,70,79;,
  3;79,70,70;,
  3;43,44,28;,
  3;28,44,27;,
  3;84,62,63;,
  3;63,62,62;,
  3;32,33,39;,
  3;39,33,38;,
  3;70,78,70;,
  3;70,78,70;,
  3;44,45,27;,
  3;27,45,26;,
  3;62,85,62;,
  3;62,85,62;,
  3;34,37,33;,
  3;33,37,38;,
  3;70,71,78;,
  3;78,71,77;,
  3;45,46,26;,
  3;26,46,25;,
  3;85,86,62;,
  3;62,86,61;,
  3;36,37,35;,
  3;35,37,34;,
  3;77,71,76;,
  3;76,71,72;,
  3;25,46,24;,
  3;24,46,47;,
  3;60,61,87;,
  3;87,61,86;,
  3;48,49,24;,
  3;24,49,25;,
  3;25,49,26;,
  3;26,49,50;,
  3;27,26,51;,
  3;51,26,50;,
  3;27,51,28;,
  3;28,51,52;,
  3;29,28,53;,
  3;53,28,52;,
  3;66,82,66;,
  3;66,82,65;,
  3;54,55,30;,
  3;30,55,31;,
  3;55,56,31;,
  3;31,56,32;,
  3;56,57,32;,
  3;32,57,33;,
  3;57,58,33;,
  3;33,58,34;,
  3;35,34,59;,
  3;59,34,58;,
  3;88,89,75;,
  3;75,89,74;,
  3;6,21,36;,
  3;36,21,37;,
  3;37,21,38;,
  3;38,21,17;,
  3;39,38,13;,
  3;13,38,17;,
  3;39,13,40;,
  3;40,13,9;,
  3;40,9,41;,
  3;41,9,7;,
  3;104,81,105;,
  3;105,81,67;,
  3;43,42,10;,
  3;10,42,5;,
  3;44,43,14;,
  3;14,43,10;,
  3;18,45,14;,
  3;14,45,44;,
  3;46,45,22;,
  3;22,45,18;,
  3;46,22,47;,
  3;47,22,4;,
  3;72,73,76;,
  3;76,73,90;,
  3;2,23,48;,
  3;48,23,49;,
  3;49,23,50;,
  3;50,23,19;,
  3;51,50,15;,
  3;15,50,19;,
  3;51,15,52;,
  3;52,15,11;,
  3;52,11,53;,
  3;53,11,3;,
  3;106,65,107;,
  3;107,65,82;,
  3;55,54,8;,
  3;8,54,1;,
  3;56,55,12;,
  3;12,55,8;,
  3;16,57,12;,
  3;12,57,56;,
  3;58,57,20;,
  3;20,57,16;,
  3;58,20,59;,
  3;59,20,0;,
  3;87,88,60;,
  3;60,88,75;,
  3;92,61,91;,
  3;91,61,60;,
  3;62,61,93;,
  3;93,61,92;,
  3;62,93,62;,
  3;62,93,62;,
  3;63,62,94;,
  3;94,62,62;,
  3;63,94,64;,
  3;64,94,95;,
  3;108,65,106;,
  3;106,65,65;,
  3;66,65,66;,
  3;66,65,65;,
  3;67,66,96;,
  3;96,66,66;,
  3;105,67,97;,
  3;97,67,96;,
  3;109,98,68;,
  3;68,98,69;,
  3;98,70,69;,
  3;69,70,70;,
  3;70,99,70;,
  3;70,99,70;,
  3;99,100,70;,
  3;70,100,71;,
  3;72,71,101;,
  3;101,71,100;,
  3;101,102,72;,
  3;72,102,73;,
  3;74,73,74;,
  3;74,73,102;,
  3;75,74,103;,
  3;103,74,74;,
  3;60,75,91;,
  3;91,75,103;,
  3;110,111,76;,
  3;76,22,77;,
  3;77,22,78;,
  3;78,22,112;,
  3;78,112,70;,
  3;70,112,113;,
  3;70,113,79;,
  3;79,113,114;,
  3;79,114,80;,
  3;80,114,115;,
  3;116,81,115;,
  3;115,81,104;,
  3;66,66,116;,
  3;116,66,81;,
  3;117,82,66;,
  3;66,82,66;,
  3;107,82,118;,
  3;118,82,117;,
  3;84,83,119;,
  3;119,83,118;,
  3;62,84,120;,
  3;120,84,119;,
  3;85,62,121;,
  3;121,62,120;,
  3;86,85,23;,
  3;122,85,121;,
  3;87,86,123;,
  3;2,86,23;,
  3;124,88,123;,
  3;123,88,87;,
  3;125,89,124;,
  3;124,89,88;,
  3;126,90,125;,
  3;125,90,89;,
  3;76,90,110;,
  3;110,90,126;,
  3;20,92,0;,
  3;123,92,91;,
  3;92,20,93;,
  3;93,20,127;,
  3;93,127,62;,
  3;62,127,128;,
  3;62,128,94;,
  3;94,128,129;,
  3;94,129,95;,
  3;95,129,130;,
  3;130,131,95;,
  3;95,131,65;,
  3;66,65,66;,
  3;66,65,131;,
  3;96,66,116;,
  3;116,66,66;,
  3;97,96,115;,
  3;115,96,116;,
  3;98,109,132;,
  3;132,97,115;,
  3;70,98,133;,
  3;133,98,132;,
  3;99,70,134;,
  3;134,70,133;,
  3;100,99,21;,
  3;135,99,134;,
  3;101,100,136;,
  3;6,100,21;,
  3;136,137,101;,
  3;101,137,102;,
  3;74,102,74;,
  3;74,102,137;,
  3;103,74,138;,
  3;138,74,74;,
  3;91,103,123;,
  3;123,103,138;;
 }
 MeshTextureCoords {
  142;
  0.625000;0.179350;,
  0.581900;0.179350;,
  0.625000;0.120830;,
  0.581900;0.120830;,
  0.625000;0.435690;,
  0.581900;0.435690;,
  0.625000;0.367500;,
  0.581900;0.367500;,
  0.581900;0.629170;,
  0.581900;0.570650;,
  0.625000;0.629170;,
  0.625000;0.570650;,
  0.625000;0.882500;,
  0.581900;0.882500;,
  0.625000;0.814310;,
  0.581900;0.814310;,
  0.810690;0.179350;,
  0.742500;0.179350;,
  0.810690;0.120830;,
  0.742500;0.120830;,
  0.189310;0.179350;,
  0.189310;0.120830;,
  0.257500;0.179350;,
  0.257500;0.120830;,
  0.525640;0.882500;,
  0.525640;0.814310;,
  0.525640;0.629170;,
  0.525640;0.570650;,
  0.525640;0.435690;,
  0.525640;0.367500;,
  0.525640;0.179350;,
  0.525640;0.120830;,
  0.467740;0.882500;,
  0.467740;0.814310;,
  0.467740;0.629170;,
  0.467740;0.570650;,
  0.467740;0.435690;,
  0.467740;0.367500;,
  0.467740;0.179350;,
  0.467740;0.120830;,
  0.409850;0.882500;,
  0.409850;0.814310;,
  0.409850;0.629170;,
  0.409850;0.570650;,
  0.409850;0.435690;,
  0.409850;0.367500;,
  0.409850;0.179350;,
  0.409850;0.120830;,
  0.375000;0.814310;,
  0.375000;0.882500;,
  0.375000;0.570650;,
  0.375000;0.629170;,
  0.375000;0.367500;,
  0.375000;0.435690;,
  0.375000;0.120830;,
  0.375000;0.179350;,
  0.375000;0.295540;,
  0.409850;0.295540;,
  0.467740;0.295540;,
  0.525640;0.295540;,
  0.581900;0.295540;,
  0.625000;0.295540;,
  0.670540;0.179350;,
  0.670540;0.120830;,
  0.625000;0.954460;,
  0.581900;0.954460;,
  0.525640;0.954460;,
  0.467740;0.954460;,
  0.409850;0.954460;,
  0.375000;0.954460;,
  0.329460;0.179350;,
  0.329460;0.120830;,
  0.375000;0.750000;,
  0.409850;0.750000;,
  0.467740;0.750000;,
  0.525640;0.750000;,
  0.581900;0.750000;,
  0.625000;0.750000;,
  0.875000;0.179350;,
  0.875000;0.120830;,
  0.581900;0.500000;,
  0.625000;0.500000;,
  0.525640;0.500000;,
  0.467740;0.500000;,
  0.409850;0.500000;,
  0.375000;0.500000;,
  0.125000;0.120830;,
  0.125000;0.179350;,
  0.375000;0.250000;,
  0.409850;0.250000;,
  0.467740;0.250000;,
  0.525640;0.250000;,
  0.581900;0.250000;,
  0.625000;0.250000;,
  0.581900;1.000000;,
  0.625000;1.000000;,
  0.525640;1.000000;,
  0.467740;1.000000;,
  0.409850;1.000000;,
  0.375000;1.000000;,
  0.409850;0.067960;,
  0.375000;0.067960;,
  0.467740;0.067960;,
  0.525640;0.067960;,
  0.581900;0.067960;,
  0.625000;0.067960;,
  0.670540;0.067960;,
  0.742500;0.067960;,
  0.810690;0.067960;,
  0.875000;0.067960;,
  0.625000;0.682040;,
  0.581900;0.682040;,
  0.525640;0.682040;,
  0.467740;0.682040;,
  0.409850;0.682040;,
  0.375000;0.682040;,
  0.125000;0.067960;,
  0.189310;0.067960;,
  0.257500;0.067960;,
  0.329460;0.067960;,
  0.810690;0.250000;,
  0.875000;0.250000;,
  0.742500;0.250000;,
  0.670540;0.250000;,
  0.329460;0.250000;,
  0.257500;0.250000;,
  0.189310;0.250000;,
  0.125000;0.250000;,
  0.409850;0.000000;,
  0.375000;0.000000;,
  0.467740;0.000000;,
  0.525640;0.000000;,
  0.581900;0.000000;,
  0.625000;0.000000;,
  0.670540;0.000000;,
  0.742500;0.000000;,
  0.810690;0.000000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.189310;0.000000;,
  0.257500;0.000000;,
  0.329460;0.000000;;
 }
}
