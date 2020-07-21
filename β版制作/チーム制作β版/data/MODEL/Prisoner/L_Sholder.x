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
 -1.36280;1.60880;2.95410;,
 -1.19980;0.42070;2.66945;,
 0.01640;1.60880;2.95410;,
 0.00380;0.42070;2.66945;,
 -3.02785;2.68330;-1.49745;,
 -3.70565;0.26690;-1.49745;,
 -3.02785;2.68330;0.10625;,
 -3.70565;0.26690;0.10625;,
 0.00380;0.42070;-2.76155;,
 -1.19980;0.42070;-2.76155;,
 0.01640;1.60880;-3.04620;,
 -1.36280;1.60880;-3.04620;,
 2.86400;2.68330;0.10625;,
 3.54180;0.26690;0.10625;,
 2.86400;2.68330;-1.49745;,
 3.54180;0.26690;-1.49745;,
 -1.36280;2.68330;-1.49745;,
 -1.36280;2.68330;0.10625;,
 0.01640;2.68330;-1.49745;,
 0.01640;2.68330;0.10625;,
 -0.87740;-9.47905;-1.29745;,
 -0.02335;-9.50235;-1.26385;,
 -0.84515;-9.50235;0.31650;,
 -0.02335;-9.50235;0.31650;,
 3.08050;-2.33210;0.19995;,
 3.08050;-2.33210;-1.41000;,
 0.00380;-2.33210;-2.76155;,
 -1.19980;-2.33210;-2.76155;,
 -3.24435;-2.33210;-1.41000;,
 -3.24435;-2.33210;0.19995;,
 -1.19980;-2.33210;2.66945;,
 0.00380;-2.33210;2.66945;,
 2.74060;-5.16525;0.19995;,
 2.74060;-5.16525;-1.41000;,
 -0.00540;-5.16525;-2.76155;,
 -1.07960;-5.16525;-2.76155;,
 -2.90445;-5.16525;-1.41000;,
 -2.90445;-5.16525;0.19995;,
 -1.07960;-5.16525;2.66945;,
 -0.00540;-5.16525;2.66945;,
 2.07730;-8.19785;0.31650;,
 2.07730;-8.19785;-1.26385;,
 -0.00540;-7.99755;-2.76155;,
 -1.07960;-7.99755;-2.76155;,
 -2.24115;-8.19785;-1.26385;,
 -2.24115;-8.19785;0.31650;,
 -1.07960;-7.99755;2.66945;,
 -0.00540;-7.99755;2.66945;,
 1.67350;-9.50235;-1.26385;,
 1.67350;-9.50235;0.31650;,
 -0.87740;-8.80830;-2.26430;,
 -0.02335;-8.78500;-2.29780;,
 -1.83725;-9.50235;0.31650;,
 -1.80505;-9.47905;-1.29745;,
 -0.02335;-8.78500;2.20570;,
 -0.84515;-8.78500;2.20570;,
 -1.83725;-9.50235;1.47355;,
 -2.24115;-8.19785;1.47355;,
 -2.90445;-5.16525;1.71235;,
 -3.24435;-2.33210;1.71235;,
 -3.70565;0.26690;1.85735;,
 -3.02785;2.68330;1.85735;,
 -1.36280;2.68330;1.85735;,
 0.01640;2.68330;1.85735;,
 2.86400;2.68330;1.85735;,
 3.54180;0.26690;1.85735;,
 3.08050;-2.33210;1.71235;,
 2.74060;-5.16525;1.71235;,
 2.07730;-8.19785;1.47355;,
 1.67350;-9.50235;1.47355;,
 -0.84515;-9.50235;1.47355;,
 -0.02335;-9.50235;1.47355;,
 1.67350;-8.78500;-2.29780;,
 1.67350;-8.19785;-2.29780;,
 2.21265;-5.16525;-2.76155;,
 2.48900;-2.33210;-2.76155;,
 2.86400;0.26690;-3.04620;,
 2.86400;1.60880;-3.04620;,
 -1.36280;1.60880;-3.04620;,
 0.01640;1.60880;-3.04620;,
 -3.02785;0.26690;-3.04620;,
 -3.02785;1.60880;-3.04620;,
 -2.65275;-2.33210;-2.76155;,
 -2.37640;-5.16525;-2.76155;,
 -1.83725;-8.19785;-2.29780;,
 -1.80505;-8.80830;-2.26430;,
 -0.02335;-8.78500;-2.29780;,
 -0.87740;-8.80830;-2.26430;,
 -1.83725;-8.78500;2.20570;,
 -1.83725;-8.19785;2.20570;,
 -2.37640;-5.16525;2.66945;,
 -2.65275;-2.33210;2.66945;,
 -3.02785;0.26690;2.95410;,
 -3.02785;1.60880;2.95410;,
 2.86400;0.26690;2.95410;,
 2.86400;1.60880;2.95410;,
 2.48900;-2.33210;2.66945;,
 2.21265;-5.16525;2.66945;,
 1.67350;-8.19785;2.20570;,
 1.67350;-8.78500;2.20570;,
 0.96520;-7.99755;2.66945;,
 0.71915;-8.78500;2.20570;,
 0.96520;-5.16525;2.66945;,
 1.09125;-2.33210;2.66945;,
 1.09125;0.42070;2.66945;,
 1.26240;1.60880;2.95410;,
 1.26240;2.68330;1.85735;,
 1.26240;2.68330;0.10625;,
 1.26240;2.68330;-1.49745;,
 1.26240;1.60880;-3.04620;,
 1.26240;1.60880;-3.04620;,
 1.09125;0.42070;-2.76155;,
 1.09125;-2.33210;-2.76155;,
 0.96520;-5.16525;-2.76155;,
 0.96520;-7.99755;-2.76155;,
 0.71915;-8.78500;-2.29780;,
 0.71915;-8.78500;-2.29780;,
 0.71915;-9.50235;-1.26385;,
 0.71915;-9.50235;0.31650;,
 0.71915;-9.50235;1.47355;,
 -3.02785;2.68330;-1.49745;,
 -3.02785;1.60880;-3.04620;,
 -3.02785;2.68330;0.10625;,
 -3.02785;2.68330;1.85735;,
 -1.83725;-9.50235;1.47355;,
 -1.83725;-9.50235;0.31650;,
 -1.80505;-9.47905;-1.29745;,
 -1.80505;-8.80830;-2.26430;,
 1.67350;-8.19785;2.20570;,
 1.67350;-8.78500;2.20570;,
 2.21265;-5.16525;2.66945;,
 2.48900;-2.33210;2.66945;,
 2.86400;0.26690;2.95410;,
 2.86400;1.60880;2.95410;,
 2.86400;2.68330;1.85735;,
 2.86400;2.68330;0.10625;,
 2.86400;2.68330;-1.49745;,
 2.86400;1.60880;-3.04620;,
 1.67350;-8.78500;-2.29780;,
 1.67350;-9.50235;-1.26385;,
 1.67350;-9.50235;0.31650;,
 1.67350;-9.50235;1.47355;;
 
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
  131;
  0.879708;0.000000;0.475515;,
  1.000000;0.000000;0.000000;,
  -0.872370;0.000000;0.488847;,
  -1.000000;0.000000;0.000000;,
  -0.997780;-0.054714;-0.037958;,
  0.879708;0.000000;-0.475515;,
  0.932718;0.019126;0.360099;,
  0.962449;0.026035;-0.270212;,
  -0.962449;0.026023;-0.270212;,
  -0.932718;0.019115;0.360098;,
  0.537781;-0.104184;0.836623;,
  0.911463;-0.136763;-0.387983;,
  -0.911444;-0.136769;-0.388026;,
  -0.538260;-0.104256;0.836305;,
  0.865065;-0.154789;0.477182;,
  0.920409;-0.153560;-0.359536;,
  -0.920386;-0.153561;-0.359595;,
  -0.865027;-0.154789;0.477251;,
  0.745168;-0.137924;0.652458;,
  0.862356;-0.127145;-0.490078;,
  -0.751935;-0.245049;-0.612001;,
  -0.821227;-0.126706;0.556356;,
  -0.953208;-0.302259;-0.005883;,
  -0.966954;-0.254950;0.000000;,
  -0.984861;-0.173344;0.000000;,
  -0.989949;-0.141429;0.000000;,
  -0.999867;0.016285;0.000000;,
  -0.962839;0.270076;0.000000;,
  0.962839;0.270076;0.000000;,
  0.999867;0.016285;0.000000;,
  0.989949;-0.141429;-0.000000;,
  0.984861;-0.173344;-0.000000;,
  0.964764;-0.263117;-0.000000;,
  0.955280;-0.295701;-0.000000;,
  0.973392;-0.195597;-0.119371;,
  0.959333;-0.255845;-0.119261;,
  0.954436;-0.163610;-0.249565;,
  0.979782;-0.147860;-0.134773;,
  0.969240;-0.000553;-0.246118;,
  0.974419;0.201642;-0.099235;,
  -0.975103;0.177550;-0.132852;,
  -0.977529;0.046660;-0.205570;,
  -0.974799;-0.153379;-0.161993;,
  -0.963940;-0.157803;-0.214286;,
  -0.956916;-0.263054;-0.122940;,
  -0.963702;-0.227856;-0.139140;,
  -0.967941;-0.192674;0.161144;,
  -0.952815;-0.257655;0.160491;,
  -0.927592;-0.166231;0.334575;,
  -0.972348;-0.149470;0.179438;,
  -0.944571;-0.005844;0.328256;,
  -0.970873;0.199769;0.132281;,
  0.968559;0.174314;0.177503;,
  0.960641;0.043058;0.274435;,
  0.964013;-0.155142;0.215893;,
  0.944209;-0.160513;0.287585;,
  0.949108;-0.248909;0.192971;,
  0.968100;-0.219879;0.120152;,
  0.000000;-0.636851;0.770987;,
  0.000000;-0.300331;0.953835;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.093818;0.995589;,
  0.000000;0.198178;0.980166;,
  0.000000;0.925828;0.377945;,
  0.000000;1.000000;0.000000;,
  0.000000;0.954365;-0.298644;,
  0.000000;-0.232991;-0.972479;,
  0.000000;-0.093818;-0.995589;,
  0.000000;0.000000;-1.000000;,
  -0.002956;-0.302729;-0.953072;,
  -0.004073;-0.711776;-0.702394;,
  -0.003984;-0.966222;-0.257679;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.925821;0.377962;,
  -0.051952;-0.619132;-0.783567;,
  -0.226700;-0.287911;-0.930438;,
  -0.076069;-0.022026;-0.996859;,
  0.047224;-0.109266;-0.992890;,
  0.056342;-0.148257;-0.987343;,
  0.000000;0.918232;-0.396043;,
  0.000000;0.946261;0.323403;,
  0.031505;0.320046;0.946878;,
  0.055095;-0.127478;0.990310;,
  -0.088987;-0.025767;0.995699;,
  -0.185751;-0.180558;0.965865;,
  0.000000;-0.595139;0.803623;,
  0.000000;-0.866402;0.499347;,
  -0.003818;-0.999985;-0.004048;,
  -0.004655;-0.952199;-0.305442;,
  0.000000;-0.616211;0.787581;,
  0.235940;-0.218578;0.946867;,
  0.079981;-0.022072;0.996552;,
  -0.048642;-0.108886;0.992863;,
  -0.032440;0.320396;0.946728;,
  0.000000;0.672845;-0.739784;,
  -0.056751;-0.127037;-0.990273;,
  0.093591;-0.025828;-0.995276;,
  0.195652;-0.181255;-0.963777;,
  0.000000;-0.680351;-0.732886;,
  0.000000;-0.954364;-0.298647;,
  0.000000;-0.925821;0.377962;,
  0.000000;0.821624;-0.570030;,
  0.000000;0.821624;-0.570030;,
  -0.086598;-0.220301;-0.971580;,
  0.000000;-0.621846;-0.783140;,
  0.000000;-0.054795;-0.998498;,
  0.000000;-0.050517;-0.998723;,
  0.053615;-0.028298;-0.998161;,
  0.110011;-0.098158;-0.989072;,
  0.000000;0.609023;-0.793153;,
  0.000000;0.980198;-0.198022;,
  0.000000;0.925828;0.377945;,
  0.000000;0.511555;0.859251;,
  0.110011;-0.098158;0.989072;,
  0.000000;-0.050517;0.998723;,
  0.000000;-0.151164;0.988509;,
  0.000000;-0.650350;0.759635;,
  0.000000;-0.968330;0.249674;,
  0.000000;-0.999954;-0.009624;,
  0.000000;-0.952188;-0.305512;,
  0.000000;-0.650350;0.759635;,
  -0.113312;-0.097248;0.988789;,
  0.000000;0.387412;0.921907;,
  0.000000;0.866415;0.499325;,
  -0.113312;-0.097248;-0.988789;,
  -0.055234;-0.028046;-0.998079;,
  0.000000;-0.050517;-0.998723;,
  0.000000;-0.151164;-0.988509;,
  0.000000;-0.680351;-0.732886;,
  0.000000;-0.918230;-0.396048;,
  -0.000000;-0.968330;0.249674;;
  224;
  3;81,82,62;,
  3;62,82,61;,
  3;40,41,27;,
  3;27,41,26;,
  3;67,77,66;,
  3;66,77,78;,
  3;28,29,39;,
  3;39,29,38;,
  3;79,64,65;,
  3;65,64,64;,
  3;88,71,87;,
  3;87,71,72;,
  3;30,37,29;,
  3;29,37,38;,
  3;67,68,77;,
  3;77,68,68;,
  3;41,42,26;,
  3;26,42,25;,
  3;82,60,61;,
  3;61,60,60;,
  3;30,31,37;,
  3;37,31,36;,
  3;68,76,68;,
  3;68,76,68;,
  3;42,43,25;,
  3;25,43,24;,
  3;60,83,60;,
  3;60,83,60;,
  3;32,35,31;,
  3;31,35,36;,
  3;68,69,76;,
  3;76,69,75;,
  3;43,44,24;,
  3;24,44,23;,
  3;83,84,60;,
  3;60,84,59;,
  3;34,35,33;,
  3;33,35,32;,
  3;75,69,74;,
  3;74,69,70;,
  3;23,44,22;,
  3;22,44,45;,
  3;58,59,85;,
  3;85,59,84;,
  3;46,47,22;,
  3;22,47,23;,
  3;23,47,24;,
  3;24,47,48;,
  3;25,24,49;,
  3;49,24,48;,
  3;25,49,26;,
  3;26,49,50;,
  3;27,26,51;,
  3;51,26,50;,
  3;64,80,64;,
  3;64,80,63;,
  3;52,53,28;,
  3;28,53,29;,
  3;53,54,29;,
  3;29,54,30;,
  3;54,55,30;,
  3;30,55,31;,
  3;55,56,31;,
  3;31,56,32;,
  3;33,32,57;,
  3;57,32,56;,
  3;86,87,73;,
  3;73,87,72;,
  3;5,19,34;,
  3;34,19,35;,
  3;35,19,36;,
  3;36,19,15;,
  3;37,36,11;,
  3;11,36,15;,
  3;37,11,38;,
  3;38,11,7;,
  3;38,7,39;,
  3;39,7,1;,
  3;101,79,102;,
  3;102,79,65;,
  3;41,40,8;,
  3;8,40,3;,
  3;42,41,12;,
  3;12,41,8;,
  3;16,43,12;,
  3;12,43,42;,
  3;44,43,20;,
  3;20,43,16;,
  3;44,20,45;,
  3;45,20,4;,
  3;70,71,74;,
  3;74,71,88;,
  3;2,21,46;,
  3;46,21,47;,
  3;47,21,48;,
  3;48,21,17;,
  3;49,48,13;,
  3;13,48,17;,
  3;49,13,50;,
  3;50,13,9;,
  3;50,9,51;,
  3;51,9,3;,
  3;62,63,81;,
  3;81,63,80;,
  3;53,52,6;,
  3;6,52,1;,
  3;54,53,10;,
  3;10,53,6;,
  3;14,55,10;,
  3;10,55,54;,
  3;56,55,18;,
  3;18,55,14;,
  3;56,18,57;,
  3;57,18,0;,
  3;85,86,58;,
  3;58,86,73;,
  3;90,59,89;,
  3;89,59,58;,
  3;60,59,91;,
  3;91,59,90;,
  3;60,91,60;,
  3;60,91,60;,
  3;61,60,92;,
  3;92,60,60;,
  3;61,92,62;,
  3;62,92,93;,
  3;93,63,62;,
  3;62,63,63;,
  3;64,63,64;,
  3;64,63,63;,
  3;65,64,65;,
  3;65,64,64;,
  3;102,65,94;,
  3;94,65,65;,
  3;103,95,66;,
  3;66,95,67;,
  3;95,68,67;,
  3;67,68,68;,
  3;68,96,68;,
  3;68,96,68;,
  3;96,97,68;,
  3;68,97,69;,
  3;70,69,98;,
  3;98,69,97;,
  3;98,99,70;,
  3;70,99,71;,
  3;72,71,72;,
  3;72,71,99;,
  3;73,72,100;,
  3;100,72,72;,
  3;58,73,89;,
  3;89,73,100;,
  3;104,105,74;,
  3;74,20,75;,
  3;75,20,76;,
  3;76,20,106;,
  3;76,106,68;,
  3;68,106,107;,
  3;68,107,77;,
  3;77,107,108;,
  3;77,108,78;,
  3;78,108,109;,
  3;110,79,109;,
  3;109,79,101;,
  3;64,64,110;,
  3;110,64,79;,
  3;111,80,64;,
  3;64,80,64;,
  3;81,80,112;,
  3;112,80,111;,
  3;82,81,113;,
  3;113,81,112;,
  3;60,82,13;,
  3;13,82,113;,
  3;83,60,114;,
  3;114,60,13;,
  3;84,83,21;,
  3;115,83,114;,
  3;85,84,116;,
  3;2,84,21;,
  3;117,86,116;,
  3;116,86,85;,
  3;118,87,117;,
  3;117,87,86;,
  3;119,88,118;,
  3;118,88,87;,
  3;74,88,104;,
  3;104,88,119;,
  3;18,90,0;,
  3;120,90,89;,
  3;90,18,91;,
  3;91,18,114;,
  3;91,114,60;,
  3;60,114,10;,
  3;60,10,92;,
  3;92,10,121;,
  3;92,121,93;,
  3;93,121,122;,
  3;122,123,93;,
  3;93,123,63;,
  3;64,63,64;,
  3;64,63,123;,
  3;65,64,110;,
  3;110,64,64;,
  3;94,65,109;,
  3;109,65,110;,
  3;95,103,124;,
  3;124,94,109;,
  3;68,95,125;,
  3;125,95,124;,
  3;96,68,126;,
  3;126,68,125;,
  3;97,96,19;,
  3;127,96,126;,
  3;98,97,128;,
  3;5,97,19;,
  3;128,129,98;,
  3;98,129,99;,
  3;72,99,72;,
  3;72,99,129;,
  3;100,72,130;,
  3;130,72,72;,
  3;89,100,120;,
  3;120,100,130;;
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
