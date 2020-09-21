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
 88;
 0.00000;38.79290;0.00000;,
 -28.17540;38.79290;0.00000;,
 -19.92300;38.79290;23.13855;,
 0.00000;38.79290;0.00000;,
 -19.92300;38.79290;-23.13855;,
 0.00000;38.79290;0.00000;,
 0.00000;38.79290;-32.72290;,
 0.00000;38.79290;0.00000;,
 19.92300;38.79290;-23.13855;,
 0.00000;38.79290;0.00000;,
 28.17540;38.79290;0.00000;,
 0.00000;38.79290;0.00000;,
 19.92300;38.79290;23.13855;,
 0.00000;38.79290;0.00000;,
 0.00000;38.79290;32.72290;,
 0.00000;38.79290;0.00000;,
 -19.92300;38.79290;23.13855;,
 0.00000;-37.30035;-0.00000;,
 -19.92300;-37.30035;23.13855;,
 -28.17540;-37.30035;0.00000;,
 0.00000;-37.30035;-0.00000;,
 -19.92300;-37.30035;-23.13855;,
 0.00000;-37.30035;-0.00000;,
 0.00000;-37.30035;-32.72290;,
 0.00000;-37.30035;-0.00000;,
 19.92300;-37.30035;-23.13855;,
 0.00000;-37.30035;-0.00000;,
 28.17540;-37.30035;-0.00000;,
 0.00000;-37.30035;-0.00000;,
 19.92300;-37.30035;23.13855;,
 0.00000;-37.30035;-0.00000;,
 0.00000;-37.30035;32.72290;,
 0.00000;-37.30035;-0.00000;,
 -19.92300;-37.30035;23.13855;,
 -25.82205;17.44415;29.98975;,
 -36.51790;17.44415;0.00000;,
 -36.51790;2.79765;0.00000;,
 -25.82205;2.79765;29.98975;,
 -25.82205;17.44415;-29.98975;,
 -25.82205;2.79765;-29.98975;,
 0.00000;17.44415;-42.41185;,
 0.00000;2.79765;-42.41185;,
 25.82205;17.44415;-29.98975;,
 25.82205;2.79765;-29.98975;,
 36.51790;17.44415;0.00000;,
 36.51790;2.79765;0.00000;,
 25.82205;17.44415;29.98975;,
 25.82205;2.79765;29.98975;,
 0.00000;17.44415;42.41185;,
 0.00000;2.79765;42.41185;,
 -25.82205;17.44415;29.98975;,
 -25.82205;2.79765;29.98975;,
 -20.76580;35.74285;24.11740;,
 -29.40215;35.65350;0.00000;,
 -20.76915;35.73090;-24.12130;,
 0.00000;35.92885;-34.02280;,
 20.65860;36.13075;-23.99290;,
 29.18120;36.21900;0.00000;,
 20.65530;36.14270;23.98905;,
 0.00000;35.94585;34.01505;,
 -20.76580;35.74285;24.11740;,
 -29.97180;-34.32740;0.00000;,
 -21.21725;-34.23670;24.64175;,
 -25.82205;-16.80790;29.98975;,
 -36.51790;-16.80790;0.00000;,
 -21.21405;-34.24895;-24.63800;,
 -25.82205;-16.80790;-29.98975;,
 0.00000;-34.04675;-34.93110;,
 0.00000;-16.80790;-42.41185;,
 21.32245;-33.83835;-24.76395;,
 25.82205;-16.80790;-29.98975;,
 30.18885;-33.74665;-0.00000;,
 36.51790;-16.80790;-0.00000;,
 21.32575;-33.82605;24.76775;,
 25.82205;-16.80790;29.98975;,
 0.00000;-34.02935;34.93860;,
 0.00000;-16.80790;42.41185;,
 -21.21725;-34.23670;24.64175;,
 -25.82205;-16.80790;29.98975;,
 -25.82205;-5.65215;29.98975;,
 -36.51790;-5.65215;0.00000;,
 -25.82205;-5.65215;-29.98975;,
 0.00000;-5.65215;-42.41185;,
 25.82205;-5.65215;-29.98975;,
 36.51790;-5.65215;-0.00000;,
 25.82205;-5.65215;29.98975;,
 0.00000;-5.65215;42.41185;,
 -25.82205;-5.65215;29.98975;;
 
 72;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;52,2,1,53;,
 4;52,53,35,34;,
 4;53,1,4,54;,
 4;53,54,38,35;,
 4;54,4,6,55;,
 4;54,55,40,38;,
 4;55,6,8,56;,
 4;55,56,42,40;,
 4;56,8,10,57;,
 4;56,57,44,42;,
 4;57,10,12,58;,
 4;57,58,46,44;,
 4;58,12,14,59;,
 4;58,59,48,46;,
 4;59,14,16,60;,
 4;59,60,50,48;,
 4;61,19,18,62;,
 4;61,62,63,64;,
 4;65,21,19,61;,
 4;65,61,64,66;,
 4;67,23,21,65;,
 4;67,65,66,68;,
 4;69,25,23,67;,
 4;69,67,68,70;,
 4;71,27,25,69;,
 4;71,69,70,72;,
 4;73,29,27,71;,
 4;73,71,72,74;,
 4;75,31,29,73;,
 4;75,73,74,76;,
 4;77,33,31,75;,
 4;77,75,76,78;,
 4;79,37,36,80;,
 4;79,80,64,63;,
 4;80,36,39,81;,
 4;80,81,66,64;,
 4;81,39,41,82;,
 4;81,82,68,66;,
 4;82,41,43,83;,
 4;82,83,70,68;,
 4;83,43,45,84;,
 4;83,84,72,70;,
 4;84,45,47,85;,
 4;84,85,74,72;,
 4;85,47,49,86;,
 4;85,86,76,74;,
 4;86,49,51,87;,
 4;86,87,78,76;;
 
 MeshMaterialList {
  3;
  72;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\materialtexture\\images.jpg";
   }
  }
  Material {
   0.357600;0.357600;0.357600;1.000000;;
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
  66;
  0.000000;1.000000;0.000000;,
  -0.138082;-0.947700;0.287746;,
  0.000000;-1.000000;-0.000000;,
  -0.137996;-0.947771;-0.287553;,
  0.001134;-0.892617;-0.450815;,
  0.354117;-0.880830;-0.314229;,
  0.139874;-0.946731;0.290061;,
  0.001126;-0.892459;0.451126;,
  -0.743506;0.000000;0.668730;,
  -1.000000;0.000000;0.000000;,
  -0.743506;0.000000;-0.668730;,
  0.000000;0.000000;-1.000000;,
  0.743506;0.000000;-0.668730;,
  1.000000;0.000000;0.000000;,
  0.743506;0.000000;0.668730;,
  0.000000;0.000000;1.000000;,
  -0.730695;-0.190690;0.655532;,
  -0.983947;-0.178459;0.000000;,
  -0.730695;-0.190690;-0.655531;,
  0.000000;-0.204822;-0.978799;,
  0.730695;-0.190690;-0.655532;,
  0.983947;-0.178459;-0.000000;,
  0.730695;-0.190690;0.655532;,
  0.000000;-0.204823;0.978799;,
  -0.729603;0.198529;0.654420;,
  -0.982571;0.185885;0.000000;,
  -0.729603;0.198528;-0.654420;,
  0.000000;0.213138;-0.977022;,
  0.729603;0.198528;-0.654420;,
  0.982571;0.185886;-0.000000;,
  0.729603;0.198529;0.654420;,
  0.000000;0.213139;0.977022;,
  -0.687271;0.387153;0.614631;,
  -0.931410;0.363971;0.000001;,
  -0.687270;0.387158;-0.614629;,
  0.000002;0.413281;-0.910603;,
  0.687271;0.387153;-0.614630;,
  0.931411;0.363970;0.000000;,
  0.687271;0.387152;0.614631;,
  0.000000;0.413277;0.910605;,
  -0.662795;-0.458262;0.592198;,
  -0.900517;-0.434821;0.000024;,
  -0.662725;-0.458515;-0.592081;,
  0.001053;-0.482661;-0.875807;,
  0.666506;-0.450532;-0.593962;,
  0.905748;-0.423816;0.000019;,
  0.666561;-0.450314;0.594066;,
  0.001045;-0.482320;0.875994;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.743506;0.000000;-0.668730;,
  1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;1.000000;,
  -0.687271;0.387155;0.614629;,
  -0.931410;0.363973;0.000001;,
  -0.687268;0.387167;-0.614625;,
  0.000002;0.413293;-0.910598;,
  0.687271;0.387156;-0.614629;,
  0.931411;0.363970;0.000000;,
  0.687271;0.387153;0.614630;,
  0.000001;0.413281;0.910603;,
  -0.857016;-0.515290;0.000048;,
  -0.819576;-0.492602;0.292640;,
  -0.819444;-0.492876;-0.292548;,
  0.869227;-0.494413;0.000039;,
  0.830362;-0.472175;0.295888;;
  72;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,1,2;,
  3;2,2,3;,
  3;2,3,4;,
  3;2,4,5;,
  3;2,5,2;,
  3;2,2,6;,
  3;2,6,7;,
  3;2,7,1;,
  4;24,25,9,8;,
  4;25,26,10,9;,
  4;26,27,11,10;,
  4;27,28,12,11;,
  4;28,29,13,12;,
  4;29,30,14,13;,
  4;30,31,15,14;,
  4;31,24,8,15;,
  4;32,53,54,33;,
  4;32,33,25,24;,
  4;33,54,55,34;,
  4;33,34,26,25;,
  4;34,55,56,35;,
  4;34,35,27,26;,
  4;35,56,57,36;,
  4;35,36,28,27;,
  4;36,57,58,37;,
  4;36,37,29,28;,
  4;37,58,59,38;,
  4;37,38,30,29;,
  4;38,59,60,39;,
  4;38,39,31,30;,
  4;39,60,53,32;,
  4;39,32,24,31;,
  4;41,61,62,40;,
  4;41,40,16,17;,
  4;42,63,61,41;,
  4;42,41,17,18;,
  4;43,4,3,42;,
  4;43,42,18,19;,
  4;44,5,4,43;,
  4;44,43,19,20;,
  4;45,64,5,44;,
  4;45,44,20,21;,
  4;46,65,64,45;,
  4;46,45,21,22;,
  4;47,7,6,46;,
  4;47,46,22,23;,
  4;40,1,7,47;,
  4;40,47,23,16;,
  4;8,8,9,48;,
  4;8,48,17,16;,
  4;48,9,10,10;,
  4;48,10,18,17;,
  4;10,10,11,49;,
  4;10,49,19,18;,
  4;49,11,12,50;,
  4;49,50,20,19;,
  4;50,12,13,51;,
  4;50,51,21,20;,
  4;51,13,14,14;,
  4;51,14,22,21;,
  4;14,14,15,52;,
  4;14,52,23,22;,
  4;52,15,8,8;,
  4;52,8,16,23;;
 }
 MeshTextureCoords {
  88;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.000000;0.250240;,
  0.125000;0.250240;,
  0.125000;0.513880;,
  0.000000;0.513880;,
  0.250000;0.250240;,
  0.250000;0.513880;,
  0.375000;0.250240;,
  0.375000;0.513880;,
  0.500000;0.250240;,
  0.500000;0.513880;,
  0.625000;0.250240;,
  0.625000;0.513880;,
  0.750000;0.250240;,
  0.750000;0.513880;,
  0.875000;0.250240;,
  0.875000;0.513880;,
  1.000000;0.250240;,
  1.000000;0.513880;,
  0.000000;0.035750;,
  0.125000;0.036800;,
  0.250000;0.035890;,
  0.375000;0.033570;,
  0.500000;0.031200;,
  0.625000;0.030170;,
  0.750000;0.031060;,
  0.875000;0.033370;,
  1.000000;0.035750;,
  0.125000;0.943130;,
  0.000000;0.942050;,
  0.000000;0.735880;,
  0.125000;0.735880;,
  0.250000;0.942200;,
  0.250000;0.735880;,
  0.375000;0.939810;,
  0.375000;0.735880;,
  0.500000;0.937340;,
  0.500000;0.735880;,
  0.625000;0.936260;,
  0.625000;0.735880;,
  0.750000;0.937190;,
  0.750000;0.735880;,
  0.875000;0.939600;,
  0.875000;0.735880;,
  1.000000;0.942050;,
  1.000000;0.735880;,
  0.000000;0.591120;,
  0.125000;0.591120;,
  0.250000;0.591120;,
  0.375000;0.591120;,
  0.500000;0.591120;,
  0.625000;0.591120;,
  0.750000;0.591120;,
  0.875000;0.591120;,
  1.000000;0.591120;;
 }
}
