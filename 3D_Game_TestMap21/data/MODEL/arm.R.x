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
 131;
 -10.52243;0.00379;-1.45122;,
 -10.52243;1.02996;-1.02617;,
 -9.50233;1.37420;-1.37041;,
 -9.50233;0.00379;-1.93805;,
 -10.52243;1.45501;0.00000;,
 -9.50233;1.94184;0.00000;,
 -10.52243;1.02996;1.02617;,
 -9.50233;1.37420;1.37041;,
 -10.52243;0.00379;1.45122;,
 -9.50233;0.00379;1.93805;,
 -10.52243;-1.02238;1.02617;,
 -9.50233;-1.36662;1.37041;,
 -10.52243;-1.44743;0.00000;,
 -9.50233;-1.93426;0.00000;,
 -10.52243;-1.02238;-1.02617;,
 -9.50233;-1.36662;-1.37041;,
 -10.52243;0.00379;-1.45122;,
 -9.50233;0.00379;-1.93805;,
 -1.03242;1.37420;-1.37041;,
 -1.03242;0.00379;-1.93805;,
 -1.03242;1.94184;0.00000;,
 -1.03242;1.37420;1.37041;,
 -1.03242;0.00379;1.93805;,
 -1.03242;-1.36662;1.37041;,
 -1.03242;-1.93426;0.00000;,
 -1.03242;-1.36662;-1.37041;,
 -1.03242;0.00379;-1.93805;,
 -0.01232;1.02996;-1.02617;,
 -0.01232;0.00379;-1.45122;,
 -0.01232;1.45501;0.00000;,
 -0.01232;1.02996;1.02617;,
 -0.01232;0.00379;1.45122;,
 -0.01232;-1.02238;1.02617;,
 -0.01232;-1.44743;0.00000;,
 -0.01232;-1.02238;-1.02617;,
 -0.01232;0.00379;-1.45122;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -10.52243;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01232;0.00379;0.00000;,
 -0.01508;1.23310;0.03100;,
 -0.34818;1.13939;0.36410;,
 -0.01508;1.13939;0.50208;,
 -0.01508;1.23310;0.03100;,
 -0.48616;1.13939;0.03100;,
 -0.01508;1.23310;0.03100;,
 -0.34818;1.13939;-0.30210;,
 -0.01508;1.23310;0.03100;,
 -0.01508;1.13939;-0.44008;,
 -0.01508;1.23310;0.03100;,
 0.31802;1.13939;-0.30210;,
 -0.01508;1.23310;0.03100;,
 0.45599;1.13939;0.03100;,
 -0.01508;1.23310;0.03100;,
 0.31802;1.13939;0.36410;,
 -0.01508;1.23310;0.03100;,
 -0.01508;1.13939;0.50208;,
 -0.63058;0.87255;0.64649;,
 -0.01508;0.87255;0.90144;,
 -0.88552;0.87255;0.03100;,
 -0.63058;0.87255;-0.58449;,
 -0.01508;0.87255;-0.83944;,
 0.60041;0.87255;-0.58449;,
 0.85536;0.87255;0.03100;,
 0.60041;0.87255;0.64649;,
 -0.01508;0.87255;0.90144;,
 -0.81927;0.47319;0.83518;,
 -0.01508;0.47319;1.16828;,
 -1.15237;0.47319;0.03100;,
 -0.81927;0.47319;-0.77318;,
 -0.01508;0.47319;-1.10629;,
 0.78910;0.47319;-0.77318;,
 1.12220;0.47319;0.03100;,
 0.78910;0.47319;0.83518;,
 -0.01508;0.47319;1.16828;,
 -0.88552;0.00211;0.90144;,
 -0.01508;0.00211;1.26199;,
 -1.24607;0.00211;0.03100;,
 -0.88552;0.00211;-0.83944;,
 -0.01508;0.00211;-1.19999;,
 0.85536;0.00211;-0.83944;,
 1.21590;0.00211;0.03100;,
 0.85536;0.00211;0.90144;,
 -0.01508;0.00211;1.26199;,
 -0.81927;-0.46897;0.83518;,
 -0.01508;-0.46897;1.16828;,
 -1.15237;-0.46897;0.03100;,
 -0.81927;-0.46897;-0.77318;,
 -0.01508;-0.46897;-1.10629;,
 0.78910;-0.46897;-0.77318;,
 1.12220;-0.46897;0.03100;,
 0.78910;-0.46897;0.83518;,
 -0.01508;-0.46897;1.16828;,
 -0.63058;-0.86833;0.64649;,
 -0.01508;-0.86833;0.90144;,
 -0.88552;-0.86833;0.03100;,
 -0.63058;-0.86833;-0.58449;,
 -0.01508;-0.86833;-0.83944;,
 0.60041;-0.86833;-0.58449;,
 0.85536;-0.86833;0.03100;,
 0.60041;-0.86833;0.64649;,
 -0.01508;-0.86833;0.90144;,
 -0.34818;-1.13518;0.36410;,
 -0.01508;-1.13518;0.50208;,
 -0.48616;-1.13518;0.03100;,
 -0.34818;-1.13518;-0.30210;,
 -0.01508;-1.13518;-0.44008;,
 0.31802;-1.13518;-0.30210;,
 0.45599;-1.13518;0.03100;,
 0.31802;-1.13518;0.36410;,
 -0.01508;-1.13518;0.50208;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;,
 -0.01508;-1.22888;0.03100;;
 
 104;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 3;36,1,0;,
 3;37,4,1;,
 3;38,6,4;,
 3;39,8,6;,
 3;40,10,8;,
 3;41,12,10;,
 3;42,14,12;,
 3;43,16,14;,
 3;44,28,27;,
 3;45,27,29;,
 3;46,29,30;,
 3;47,30,31;,
 3;48,31,32;,
 3;49,32,33;,
 3;50,33,34;,
 3;51,34,35;,
 3;52,53,54;,
 3;55,56,53;,
 3;57,58,56;,
 3;59,60,58;,
 3;61,62,60;,
 3;63,64,62;,
 3;65,66,64;,
 3;67,68,66;,
 4;54,53,69,70;,
 4;53,56,71,69;,
 4;56,58,72,71;,
 4;58,60,73,72;,
 4;60,62,74,73;,
 4;62,64,75,74;,
 4;64,66,76,75;,
 4;66,68,77,76;,
 4;70,69,78,79;,
 4;69,71,80,78;,
 4;71,72,81,80;,
 4;72,73,82,81;,
 4;73,74,83,82;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;79,78,87,88;,
 4;78,80,89,87;,
 4;80,81,90,89;,
 4;81,82,91,90;,
 4;82,83,92,91;,
 4;83,84,93,92;,
 4;84,85,94,93;,
 4;85,86,95,94;,
 4;88,87,96,97;,
 4;87,89,98,96;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;91,92,101,100;,
 4;92,93,102,101;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 4;97,96,105,106;,
 4;96,98,107,105;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 4;101,102,111,110;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;106,105,114,115;,
 4;105,107,116,114;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;110,111,120,119;,
 4;111,112,121,120;,
 4;112,113,122,121;,
 3;115,114,123;,
 3;114,116,124;,
 3;116,117,125;,
 3;117,118,126;,
 3;118,119,127;,
 3;119,120,128;,
 3;120,121,129;,
 3;121,122,130;;
 
 MeshMaterialList {
  1;
  104;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.056800;0.056800;0.056800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.014200;0.014200;0.014200;;
  }
 }
 MeshNormals {
  90;
  -1.000000;0.000000;0.000000;,
  -0.430703;-0.000000;-0.902494;,
  -0.430704;0.638159;-0.638159;,
  -0.430703;0.902494;0.000000;,
  -0.430704;0.638159;0.638159;,
  -0.430703;-0.000000;0.902494;,
  -0.430704;-0.638159;0.638159;,
  -0.430703;-0.902494;0.000000;,
  -0.430704;-0.638159;-0.638159;,
  -0.222321;-0.000000;-0.974973;,
  -0.222322;0.689410;-0.689410;,
  -0.222321;0.974973;0.000000;,
  -0.222322;0.689410;0.689410;,
  -0.222321;-0.000000;0.974973;,
  -0.222322;-0.689410;0.689410;,
  -0.222321;-0.974973;0.000000;,
  -0.222322;-0.689410;-0.689410;,
  0.222321;-0.000000;-0.974973;,
  0.222321;0.689410;-0.689410;,
  0.222321;0.974973;0.000000;,
  0.222321;0.689410;0.689410;,
  0.222321;-0.000000;0.974973;,
  0.222321;-0.689410;0.689410;,
  0.222321;-0.974973;-0.000000;,
  0.222321;-0.689410;-0.689410;,
  0.430703;0.000000;-0.902494;,
  0.430704;0.638159;-0.638159;,
  0.430703;0.902494;0.000000;,
  0.430704;0.638159;0.638159;,
  0.430703;0.000000;0.902494;,
  0.430704;-0.638159;0.638159;,
  0.430703;-0.902494;-0.000000;,
  0.430704;-0.638159;-0.638159;,
  1.000000;0.000000;0.000000;,
  0.000001;1.000000;0.000000;,
  0.000001;0.924735;0.380612;,
  -0.269134;0.924734;0.269134;,
  -0.380610;0.924735;-0.000000;,
  -0.269134;0.924734;-0.269134;,
  0.000001;0.924735;-0.380612;,
  0.269137;0.924734;-0.269133;,
  0.380614;0.924734;-0.000000;,
  0.269137;0.924734;0.269133;,
  0.000002;0.709234;0.704973;,
  -0.498490;0.709236;0.498490;,
  -0.704968;0.709239;-0.000000;,
  -0.498490;0.709238;-0.498487;,
  0.000002;0.709238;-0.704969;,
  0.498493;0.709234;-0.498489;,
  0.704972;0.709235;-0.000000;,
  0.498493;0.709233;0.498491;,
  0.000002;0.384553;0.923103;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652735;0.384551;-0.652731;,
  0.000002;0.384554;-0.923102;,
  0.652736;0.384552;-0.652730;,
  0.923104;0.384550;0.000000;,
  0.652734;0.384552;0.652732;,
  0.000001;-0.000000;1.000000;,
  -0.707106;0.000000;0.707107;,
  -0.707108;0.000000;-0.707106;,
  0.000001;0.000000;-1.000000;,
  0.707110;0.000000;-0.707103;,
  0.707109;-0.000000;0.707105;,
  0.000002;-0.384553;0.923103;,
  -0.652732;-0.384551;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652735;-0.384551;-0.652731;,
  0.000002;-0.384554;-0.923102;,
  0.652736;-0.384552;-0.652730;,
  0.923104;-0.384550;-0.000000;,
  0.652734;-0.384552;0.652732;,
  0.000002;-0.709227;0.704980;,
  -0.498495;-0.709229;0.498495;,
  -0.704976;-0.709232;0.000000;,
  -0.498495;-0.709231;-0.498492;,
  0.000002;-0.709231;-0.704976;,
  0.498498;-0.709228;-0.498494;,
  0.704979;-0.709228;0.000000;,
  0.498498;-0.709226;0.498496;,
  0.000001;-0.924735;0.380611;,
  -0.269134;-0.924735;0.269134;,
  -0.380609;-0.924736;0.000000;,
  -0.269133;-0.924735;-0.269133;,
  0.000001;-0.924735;-0.380611;,
  0.269136;-0.924734;-0.269132;,
  0.380613;-0.924735;0.000000;,
  0.269136;-0.924734;0.269132;,
  0.000001;-1.000000;-0.000000;;
  104;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;33,33,33;,
  3;33,33,33;,
  3;33,33,33;,
  3;33,33,33;,
  3;33,33,33;,
  3;33,33,33;,
  3;33,33,33;,
  3;33,33,33;,
  3;34,36,35;,
  3;34,37,36;,
  3;34,38,37;,
  3;34,39,38;,
  3;34,40,39;,
  3;34,41,40;,
  3;34,42,41;,
  3;34,35,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,35,43,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,43,51,58;,
  4;51,52,60,59;,
  4;52,53,0,60;,
  4;53,54,61,0;,
  4;54,55,62,61;,
  4;55,56,63,62;,
  4;56,57,33,63;,
  4;57,58,64,33;,
  4;58,51,59,64;,
  4;59,60,66,65;,
  4;60,0,67,66;,
  4;0,61,68,67;,
  4;61,62,69,68;,
  4;62,63,70,69;,
  4;63,33,71,70;,
  4;33,64,72,71;,
  4;64,59,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,73,81,88;,
  3;81,82,89;,
  3;82,83,89;,
  3;83,84,89;,
  3;84,85,89;,
  3;85,86,89;,
  3;86,87,89;,
  3;87,88,89;,
  3;88,81,89;;
 }
 MeshTextureCoords {
  131;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.333330;,
  0.000000;0.333330;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.375000;0.000000;,
  0.375000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.625000;0.000000;,
  0.625000;0.333330;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  0.875000;0.000000;,
  0.875000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.125000;0.666670;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.375000;0.666670;,
  0.500000;0.666670;,
  0.625000;0.666670;,
  0.750000;0.666670;,
  0.875000;0.666670;,
  1.000000;0.666670;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
