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
 107;
 0.18351;-2.88734;-3.93465;,
 0.18351;-6.31487;-3.58508;,
 -1.36064;-6.31487;-3.58508;,
 -1.50989;-2.88734;-3.93465;,
 -1.36064;0.30499;1.84017;,
 0.18351;0.30499;1.84017;,
 0.18351;0.30499;0.03175;,
 -1.36064;0.30499;0.03175;,
 0.18351;-6.31487;3.64858;,
 0.18351;-2.88734;3.99816;,
 -1.50989;-2.88734;3.99816;,
 -1.36064;-6.31487;3.64858;,
 0.18351;-9.84009;0.03175;,
 -1.36064;-9.16994;1.84017;,
 -1.36064;-9.53690;0.03175;,
 -3.20327;-2.88734;0.03175;,
 -2.90478;-6.31487;0.03175;,
 -2.90478;-6.31487;1.84017;,
 -3.20327;-2.88734;2.01495;,
 3.57027;-2.88734;2.01495;,
 3.27178;-6.31487;1.84017;,
 3.27178;-6.31487;0.03175;,
 3.57027;-2.88734;0.03175;,
 0.18351;-7.65363;-3.13986;,
 -1.17056;-7.65363;-3.13986;,
 -2.52462;-7.65363;0.03175;,
 -2.52462;-7.65363;1.61757;,
 0.18351;-7.65363;3.20337;,
 -1.17056;-7.65363;3.20337;,
 2.89162;-7.65363;1.61757;,
 2.89162;-7.65363;0.03175;,
 0.18351;-1.09146;3.64858;,
 -1.36064;-1.09146;3.64858;,
 -2.90478;-1.09146;0.03175;,
 -2.90478;-1.09146;1.84017;,
 0.18351;-1.09146;-3.58508;,
 -1.36064;-1.09146;-3.58508;,
 3.27178;-1.09146;1.84017;,
 3.27178;-1.09146;0.03175;,
 1.72764;-9.16994;1.84017;,
 0.18351;-9.53690;1.84017;,
 1.53756;-7.65363;3.20337;,
 1.72764;-6.31487;3.64858;,
 1.87689;-2.88734;3.99816;,
 1.72764;-1.09146;3.64858;,
 1.72764;0.30499;1.84017;,
 1.72764;0.30499;0.03175;,
 1.72764;-1.09146;-3.58508;,
 1.87689;-2.88734;-3.93465;,
 1.72764;-6.31487;-3.58508;,
 1.53756;-7.65363;-3.13986;,
 1.72764;0.30499;-1.77666;,
 0.18351;0.30499;-1.77666;,
 -1.36064;0.30499;-1.77666;,
 -2.90478;-1.09146;-1.77666;,
 -3.20327;-2.88734;-1.95144;,
 -2.90478;-6.31487;-1.77666;,
 -2.52462;-7.65363;-1.55406;,
 -1.36064;-9.16994;-1.77666;,
 0.18351;-9.53690;-1.77666;,
 1.72764;-9.16994;-1.77666;,
 2.89162;-7.65363;-1.55406;,
 3.27178;-6.31487;-1.77666;,
 3.57027;-2.88734;-1.95144;,
 3.27178;-1.09146;-1.77666;,
 2.89162;-7.65363;0.03175;,
 1.72764;-9.53690;0.03175;,
 2.89162;-7.65363;-1.55406;,
 2.89162;-7.65363;1.61757;,
 2.61418;-6.31487;2.86242;,
 2.31498;-7.65363;2.51397;,
 2.84911;-2.88734;3.13600;,
 2.38366;-1.09146;3.10731;,
 3.27178;-1.09146;0.03175;,
 3.27178;-1.09146;1.84017;,
 3.27178;-1.09146;-1.77666;,
 3.07296;-2.88734;-2.74934;,
 2.89194;-1.09146;-2.67411;,
 2.81830;-6.31487;-2.50424;,
 2.49397;-7.65363;-2.19207;,
 -2.24718;-6.31487;2.86242;,
 -1.94798;-7.65363;2.51397;,
 -2.52462;-7.65363;0.03175;,
 -2.52462;-7.65363;1.61757;,
 -2.52462;-7.65363;-1.55406;,
 -2.12697;-7.65363;-2.19207;,
 -2.45130;-6.31487;-2.50424;,
 -2.70596;-2.88734;-2.74934;,
 -2.52494;-1.09146;-2.67411;,
 -2.90478;-1.09146;0.03175;,
 -2.90478;-1.09146;-1.77666;,
 -2.90478;-1.09146;1.84017;,
 -2.01666;-1.09146;3.10731;,
 -2.48210;-2.88734;3.13600;,
 -2.12697;-7.65363;-2.19207;,
 0.18351;-7.65363;-3.13986;,
 -1.17056;-7.65363;-3.13986;,
 1.53756;-7.65363;-3.13986;,
 2.49397;-7.65363;-2.19207;,
 -1.94798;-7.65363;2.51397;,
 -2.24718;-6.31487;2.86242;,
 -2.48210;-2.88734;3.13600;,
 -2.01666;-1.09146;3.10731;,
 2.84911;-2.88734;3.13600;,
 2.38366;-1.09146;3.10731;,
 2.61418;-6.31487;2.86242;,
 2.31498;-7.65363;2.51397;;
 
 92;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 3;12,13,14;,
 4;15,16,17,18;,
 4;19,20,21,22;,
 4;1,23,24,2;,
 4;16,25,26,17;,
 4;27,8,11,28;,
 4;20,29,30,21;,
 4;9,31,32,10;,
 4;33,15,18,34;,
 4;35,0,3,36;,
 4;37,19,22,38;,
 3;12,39,40;,
 4;41,42,8,27;,
 4;42,43,9,8;,
 4;43,44,31,9;,
 4;5,45,46,6;,
 4;47,48,0,35;,
 4;48,49,1,0;,
 4;49,50,23,1;,
 4;46,51,52,6;,
 4;52,53,7,6;,
 4;54,55,15,33;,
 4;55,56,16,15;,
 4;56,57,25,16;,
 3;58,12,14;,
 3;59,60,12;,
 4;21,30,61,62;,
 4;22,21,62,63;,
 4;38,22,63,64;,
 4;65,66,60,67;,
 4;68,39,66,65;,
 4;69,42,41,70;,
 4;71,43,42,69;,
 4;72,44,43,71;,
 4;73,46,45,74;,
 4;75,51,46,73;,
 4;76,48,47,77;,
 4;78,49,48,76;,
 4;79,50,49,78;,
 4;28,11,80,81;,
 4;82,14,13,83;,
 4;84,58,14,82;,
 4;2,24,85,86;,
 4;3,2,86,87;,
 4;36,3,87,88;,
 4;89,7,53,90;,
 4;91,4,7,89;,
 4;10,32,92,93;,
 4;11,10,93,80;,
 3;77,51,75;,
 4;52,51,47,35;,
 4;36,53,52,35;,
 3;88,53,36;,
 4;87,55,54,88;,
 4;86,56,55,87;,
 4;85,57,56,86;,
 3;94,58,84;,
 4;95,59,58,96;,
 4;97,60,59,95;,
 3;98,60,97;,
 4;62,61,79,78;,
 4;63,62,78,76;,
 4;64,63,76,77;,
 3;70,41,39;,
 4;40,39,41,27;,
 4;28,13,40,27;,
 3;83,13,81;,
 4;17,26,99,100;,
 4;18,17,100,101;,
 4;34,18,101,102;,
 3;32,4,92;,
 4;31,5,4,32;,
 4;44,45,5,31;,
 3;74,45,72;,
 4;103,19,37,104;,
 4;105,20,19,103;,
 4;106,29,20,105;,
 3;67,60,98;,
 3;12,60,66;,
 3;40,13,12;,
 3;81,13,28;,
 3;96,58,94;,
 3;58,59,12;,
 3;66,39,12;,
 3;70,39,68;,
 3;77,47,51;,
 3;90,53,88;,
 3;92,4,91;,
 3;72,45,44;;
 
 MeshMaterialList {
  11;
  92;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.357647;0.000000;0.326275;1.000000;;
   5.000000;
   0.810000;0.810000;0.810000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.671373;0.467451;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.240000;0.240000;0.240000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.116078;0.116078;0.116078;1.000000;;
   5.000000;
   0.880000;0.880000;0.880000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.442353;0.006275;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.423529;0.338824;0.495686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.263529;0.015686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.517647;0.517647;0.517647;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.172549;0.112941;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.727843;0.238431;1.000000;;
   25.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  0.713813;-0.406886;-0.570013;,
  -0.713813;-0.406886;-0.570013;,
  0.700737;0.462389;-0.543289;,
  -0.700737;0.462389;-0.543289;,
  0.657640;0.464177;0.593337;,
  -0.657641;0.464176;0.593337;,
  0.691294;-0.414604;0.591790;,
  -0.691294;-0.414604;0.591790;,
  0.763981;-0.211128;-0.609720;,
  -0.763981;-0.211128;-0.609720;,
  -0.741917;-0.213637;0.635545;,
  0.741917;-0.213638;0.635545;,
  0.752337;0.047893;0.657035;,
  -0.752337;0.047893;0.657036;,
  -0.784424;0.023134;-0.619793;,
  0.784424;0.023134;-0.619793;,
  0.000000;-0.479550;-0.877514;,
  0.000000;-0.479550;0.877514;,
  0.000000;-0.209775;0.977750;,
  0.000000;0.045290;0.998974;,
  0.000000;0.525025;0.851087;,
  0.000000;0.525025;-0.851087;,
  0.000000;0.045290;-0.998974;,
  0.000000;-0.209775;-0.977750;,
  0.877515;0.479549;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.877515;0.479549;0.000000;,
  -0.999243;0.038908;0.000000;,
  -0.983525;-0.180773;0.000000;,
  -0.904595;-0.426273;0.000000;,
  0.000001;-1.000000;0.000000;,
  0.904595;-0.426273;0.000000;,
  0.983525;-0.180773;-0.000000;,
  0.999243;0.038907;0.000000;,
  0.361735;-0.466051;-0.807431;,
  0.551249;-0.834341;0.000000;,
  0.336280;-0.470546;0.815784;,
  0.345276;-0.226920;0.910655;,
  0.350290;0.047210;0.935451;,
  0.301472;0.520470;0.798890;,
  0.359384;0.933190;0.000000;,
  0.302186;0.512537;-0.803735;,
  0.367387;0.035634;-0.929385;,
  0.370537;-0.227137;-0.900617;,
  -0.345277;-0.226919;0.910654;,
  -0.336280;-0.470546;0.815784;,
  -0.551248;-0.834341;0.000000;,
  -0.361735;-0.466051;-0.807431;,
  -0.370537;-0.227137;-0.900617;,
  -0.367387;0.035634;-0.929385;,
  -0.302186;0.512537;-0.803735;,
  -0.359384;0.933190;0.000000;,
  -0.301473;0.520470;0.798890;,
  -0.350292;0.047210;0.935450;,
  0.856965;0.476547;-0.196249;,
  0.383128;0.868406;-0.314778;,
  0.000000;0.946437;-0.322887;,
  -0.383128;0.868406;-0.314778;,
  -0.856965;0.476547;-0.196249;,
  -0.966132;0.032907;-0.255941;,
  -0.941923;-0.201698;-0.268512;,
  -0.864079;-0.428850;-0.263545;,
  -0.494110;-0.760747;-0.420856;,
  0.000001;-0.861168;-0.508321;,
  0.494110;-0.760746;-0.420856;,
  0.864079;-0.428850;-0.263545;,
  0.941923;-0.201698;-0.268512;,
  0.966132;0.032907;-0.255941;,
  0.862407;-0.428160;0.270061;,
  0.484398;-0.763712;0.426735;,
  0.000001;-0.861168;0.508321;,
  -0.484397;-0.763713;0.426735;,
  -0.862407;-0.428160;0.270061;,
  -0.939918;-0.202049;0.275192;,
  -0.957149;0.047301;0.285708;,
  -0.835052;0.482901;0.263618;,
  -0.379017;0.857841;0.347066;,
  0.000000;0.946437;0.322887;,
  0.379017;0.857841;0.347066;,
  0.835052;0.482901;0.263617;,
  0.957149;0.047301;0.285706;,
  0.939918;-0.202050;0.275191;;
  92;
  4;22,23,48,49;,
  4;76,77,25,51;,
  4;18,19,53,44;,
  3;30,71,46;,
  4;27,28,73,74;,
  4;80,81,32,33;,
  4;23,16,47,48;,
  4;28,29,72,73;,
  4;17,18,44,45;,
  4;81,68,31,32;,
  4;19,20,52,53;,
  4;26,27,74,75;,
  4;21,22,49,50;,
  4;79,80,33,24;,
  3;30,69,70;,
  4;36,37,18,17;,
  4;37,38,19,18;,
  4;38,39,20,19;,
  4;77,78,40,25;,
  4;41,42,22,21;,
  4;42,43,23,22;,
  4;43,34,16,23;,
  4;40,55,56,25;,
  4;56,57,51,25;,
  4;58,59,27,26;,
  4;59,60,28,27;,
  4;60,61,29,28;,
  3;62,30,46;,
  3;63,64,30;,
  4;32,31,65,66;,
  4;33,32,66,67;,
  4;24,33,67,54;,
  4;31,35,64,65;,
  4;68,69,35,31;,
  4;11,37,36,6;,
  4;12,38,37,11;,
  4;4,39,38,12;,
  4;24,40,78,79;,
  4;54,55,40,24;,
  4;15,42,41,2;,
  4;8,43,42,15;,
  4;0,34,43,8;,
  4;45,44,10,7;,
  4;29,46,71,72;,
  4;61,62,46,29;,
  4;48,47,1,9;,
  4;49,48,9,14;,
  4;50,49,14,3;,
  4;26,51,57,58;,
  4;75,76,51,26;,
  4;53,52,5,13;,
  4;44,53,13,10;,
  3;2,55,54;,
  4;56,55,41,21;,
  4;50,57,56,21;,
  3;3,57,50;,
  4;14,59,58,3;,
  4;9,60,59,14;,
  4;1,61,60,9;,
  3;1,62,61;,
  4;16,63,62,47;,
  4;34,64,63,16;,
  3;0,64,34;,
  4;66,65,0,8;,
  4;67,66,8,15;,
  4;54,67,15,2;,
  3;6,36,69;,
  4;70,69,36,17;,
  4;45,71,70,17;,
  3;72,71,7;,
  4;73,72,7,10;,
  4;74,73,10,13;,
  4;75,74,13,5;,
  3;52,76,5;,
  4;20,77,76,52;,
  4;39,78,77,20;,
  3;79,78,4;,
  4;12,80,79,4;,
  4;11,81,80,12;,
  4;6,68,81,11;,
  3;65,64,0;,
  3;30,64,35;,
  3;70,71,30;,
  3;7,71,45;,
  3;47,62,1;,
  3;62,63,30;,
  3;35,69,30;,
  3;6,69,68;,
  3;2,41,55;,
  3;58,57,3;,
  3;5,76,75;,
  3;4,78,39;;
 }
 MeshTextureCoords {
  107;
  0.500000;0.115461;,
  0.500000;0.051003;,
  0.562500;0.051003;,
  0.562500;0.115461;,
  0.562500;0.437500;,
  0.500000;0.437500;,
  0.500000;0.375000;,
  0.562500;0.375000;,
  0.500000;0.698997;,
  0.500000;0.634539;,
  0.562500;0.634539;,
  0.562500;0.698997;,
  0.500000;0.875000;,
  0.562500;0.812500;,
  0.562500;0.875000;,
  0.750000;0.115461;,
  0.750000;0.051003;,
  0.812500;0.051003;,
  0.812500;0.115461;,
  0.187500;0.115461;,
  0.187500;0.051003;,
  0.250000;0.051003;,
  0.250000;0.115461;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.500000;0.750000;,
  0.562500;0.750000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.750000;0.250000;,
  0.812500;0.250000;,
  0.500000;0.250000;,
  0.562500;0.250000;,
  0.187500;0.250000;,
  0.250000;0.250000;,
  0.437500;0.812500;,
  0.500000;0.812500;,
  0.437500;0.750000;,
  0.437500;0.698997;,
  0.437500;0.634539;,
  0.437500;0.500000;,
  0.437500;0.437500;,
  0.437500;0.375000;,
  0.437500;0.250000;,
  0.437500;0.115461;,
  0.437500;0.051003;,
  0.437500;0.000000;,
  0.437500;0.312500;,
  0.500000;0.312500;,
  0.562500;0.312500;,
  0.687500;0.250000;,
  0.687500;0.115461;,
  0.687500;0.051003;,
  0.687500;0.000000;,
  0.562500;0.937500;,
  0.500000;0.937500;,
  0.437500;0.937500;,
  0.312500;0.000000;,
  0.312500;0.051003;,
  0.312500;0.115461;,
  0.312500;0.250000;,
  0.375000;0.875000;,
  0.437500;0.875000;,
  0.375000;0.937500;,
  0.375000;0.812500;,
  0.375000;0.698997;,
  0.375000;0.750000;,
  0.375000;0.634539;,
  0.375000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.437500;,
  0.375000;0.312500;,
  0.375000;0.115461;,
  0.375000;0.250000;,
  0.375000;0.051003;,
  0.375000;0.000000;,
  0.625000;0.698997;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;0.812500;,
  0.625000;0.937500;,
  0.625000;0.000000;,
  0.625000;0.051003;,
  0.625000;0.115461;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.312500;,
  0.625000;0.437500;,
  0.625000;0.500000;,
  0.625000;0.634539;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.437500;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.051003;,
  0.875000;0.115461;,
  0.875000;0.250000;,
  0.125000;0.115461;,
  0.125000;0.250000;,
  0.125000;0.051003;,
  0.125000;0.000000;;
 }
}
