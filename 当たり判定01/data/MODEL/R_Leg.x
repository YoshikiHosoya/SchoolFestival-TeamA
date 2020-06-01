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
 92;
 1.85487;-4.78889;1.50146;,
 1.85487;-4.78889;-1.54222;,
 1.85487;0.22541;-1.54222;,
 1.85487;0.22541;1.50146;,
 -0.91793;0.22541;-1.54222;,
 -0.91793;0.22541;1.50146;,
 -0.91793;-4.78889;-1.54222;,
 -0.91793;-4.78889;1.50146;,
 1.85487;-4.78889;-1.54222;,
 1.85487;-4.78889;1.50146;,
 -0.91793;-4.78889;-1.54222;,
 -0.91793;0.22541;-1.54222;,
 -0.91793;-4.78889;1.50146;,
 -0.91793;0.22541;1.50146;,
 1.03040;-3.33346;-2.14307;,
 1.03040;0.12968;-2.14307;,
 1.14158;-3.33346;-1.90466;,
 1.15720;0.12968;-1.87115;,
 1.25274;-3.33346;-1.66625;,
 1.25274;0.12968;-1.66625;,
 -1.64386;0.12968;-0.56499;,
 -0.68940;0.12968;-2.17467;,
 -1.77066;0.12968;-0.83692;,
 -0.80430;0.12968;-2.42108;,
 -1.54831;0.12968;-0.36010;,
 -1.54831;-4.16924;-0.36010;,
 -1.65949;-4.16924;-0.59851;,
 -1.77066;-4.16924;-0.83692;,
 -0.67791;-3.33346;-2.15003;,
 -1.16870;-4.16924;-1.37427;,
 -1.28748;-4.16924;-1.62900;,
 -0.80430;-3.33346;-2.42108;,
 -0.80430;-3.33346;-2.42108;,
 -0.80430;0.12968;-2.42108;,
 0.11305;-3.33346;-2.28208;,
 -0.55152;0.12968;-1.87897;,
 0.35062;-3.33346;-1.77261;,
 -0.55152;-3.33346;-1.87897;,
 -1.77066;-4.16924;-0.83692;,
 -1.77066;0.12968;-0.83692;,
 -1.28748;-4.16924;-1.62900;,
 -0.55152;0.12968;-1.87897;,
 -1.54831;0.12968;-0.36010;,
 -1.04992;-4.16924;-1.11954;,
 -1.54831;-4.16924;-0.36010;,
 1.14158;-3.33346;-1.90466;,
 0.23183;-3.33346;-2.02735;,
 0.11305;-3.33346;-2.28208;,
 1.03040;-3.33346;-2.14307;,
 0.35062;-3.33346;-1.77261;,
 1.25274;-3.33346;-1.66625;,
 -1.04992;-4.16924;-1.11954;,
 -0.55152;-3.33346;-1.87897;,
 -1.77066;0.20693;0.85828;,
 -1.64386;0.20693;0.58635;,
 -1.77066;-2.40246;0.85828;,
 -1.65949;-2.40246;0.61987;,
 -1.54831;0.20693;0.38145;,
 -1.54831;-2.40246;0.38145;,
 -0.80430;0.20693;2.44244;,
 1.03040;0.20693;2.16444;,
 -0.68940;0.20693;2.19603;,
 1.15720;0.20693;1.89251;,
 1.25274;0.20693;1.68761;,
 1.25274;-1.89516;1.68761;,
 1.14158;-1.89516;1.92602;,
 1.03040;-1.89516;2.16444;,
 -1.65949;-2.40246;0.61987;,
 -1.16870;-2.40246;1.39563;,
 -1.28748;-2.40246;1.65036;,
 -1.77066;-2.40246;0.85828;,
 -0.80430;-1.89516;2.44244;,
 -0.80430;0.20693;2.44244;,
 -1.28748;-2.40246;1.65036;,
 -1.04992;-2.40246;1.14089;,
 -0.55152;0.20693;1.90033;,
 -0.55152;-1.89516;1.90033;,
 1.03040;0.20693;2.16444;,
 1.03040;-1.89516;2.16444;,
 0.11305;-1.89516;2.30344;,
 -0.55152;0.20693;1.90033;,
 0.35062;-1.89516;1.79397;,
 1.25274;0.20693;1.68761;,
 1.25274;-1.89516;1.68761;,
 0.23183;-1.89516;2.04870;,
 0.11305;-1.89516;2.30344;,
 -0.67791;-1.89516;2.17139;,
 -0.80430;-1.89516;2.44244;,
 -1.04992;-2.40246;1.14089;,
 -1.54831;-2.40246;0.38145;,
 -0.55152;-1.89516;1.90033;,
 0.35062;-1.89516;1.79397;;
 
 78;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 3;14,15,16;,
 3;15,17,16;,
 3;16,17,18;,
 3;17,19,18;,
 3;20,21,22;,
 3;22,21,23;,
 3;17,15,21;,
 3;15,23,21;,
 3;24,20,25;,
 3;25,20,26;,
 3;20,22,26;,
 3;22,27,26;,
 4;28,29,30,31;,
 3;32,33,34;,
 3;34,33,14;,
 3;33,15,14;,
 3;19,35,18;,
 3;18,35,36;,
 3;35,37,36;,
 3;38,39,40;,
 3;39,33,40;,
 3;33,32,40;,
 3;24,41,20;,
 3;20,41,21;,
 3;19,17,41;,
 3;17,21,41;,
 3;35,42,37;,
 3;37,42,43;,
 3;42,44,43;,
 4;45,46,47,48;,
 4;49,46,45,50;,
 4;51,29,28,52;,
 4;25,26,29,51;,
 4;30,29,26,27;,
 4;52,28,46,49;,
 4;47,46,28,31;,
 3;53,54,55;,
 3;55,54,56;,
 3;54,57,56;,
 3;57,58,56;,
 3;59,60,61;,
 3;60,62,61;,
 3;59,61,53;,
 3;61,54,53;,
 3;63,62,64;,
 3;64,62,65;,
 3;62,60,65;,
 3;60,66,65;,
 4;67,68,69,70;,
 3;71,72,73;,
 3;72,53,73;,
 3;53,55,73;,
 3;58,57,74;,
 3;57,75,74;,
 3;75,76,74;,
 3;77,72,78;,
 3;78,72,79;,
 3;72,71,79;,
 3;61,62,80;,
 3;62,63,80;,
 3;61,80,54;,
 3;80,57,54;,
 3;76,75,81;,
 3;75,82,81;,
 3;82,83,81;,
 4;84,65,66,85;,
 4;68,86,87,69;,
 4;86,84,85,87;,
 4;88,68,67,89;,
 4;90,86,68,88;,
 4;91,84,86,90;,
 4;64,65,84,91;;
 
 MeshMaterialList {
  6;
  78;
  2,
  2,
  2,
  4,
  2,
  2,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  4,
  5,
  4,
  4,
  4,
  5,
  4,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  4,
  5,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.024000;0.024000;0.024000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.152000;0.152000;0.152000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.264000;0.264000;0.264000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.592000;0.592000;0.592000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536800;0.536800;0.536800;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.640000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  69;
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.906322;0.000001;-0.422587;,
  0.448972;0.000001;-0.893546;,
  0.906319;0.000000;-0.422595;,
  0.730612;0.000001;-0.682793;,
  -0.906294;0.000000;0.422648;,
  -0.906295;-0.000000;0.422645;,
  -0.998448;0.000000;-0.055684;,
  0.363185;-0.916197;-0.169352;,
  0.906317;0.000001;-0.422599;,
  -0.117088;-0.000000;0.993122;,
  -0.117086;0.000000;0.993122;,
  0.906309;0.000001;-0.422615;,
  0.363187;-0.916196;-0.169352;,
  -0.906307;-0.000000;0.422621;,
  0.836041;-0.000001;0.548668;,
  -0.117088;-0.000000;0.993122;,
  0.000000;-1.000000;-0.000000;,
  0.149819;0.000001;-0.988714;,
  -0.906303;0.000000;-0.422627;,
  -0.992678;-0.000000;-0.120794;,
  -0.906303;-0.000000;-0.422629;,
  -0.973090;-0.000000;0.230428;,
  0.906319;0.000000;0.422595;,
  0.906322;0.000001;0.422587;,
  0.448971;0.000000;0.893546;,
  -0.853698;0.000000;0.520768;,
  -0.906308;-0.000000;-0.422617;,
  0.836040;-0.000001;-0.548668;,
  0.836039;0.000000;-0.548670;,
  -0.117088;-0.000000;-0.993122;,
  0.149813;0.000000;0.988714;,
  0.836042;-0.000001;-0.548666;,
  0.259587;-0.958104;0.121045;,
  -0.906305;-0.000000;-0.422623;,
  0.259589;-0.958103;0.121043;,
  0.906314;0.000001;0.422606;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.906301;-0.000000;0.422633;,
  -0.998448;-0.000000;-0.055685;,
  0.149813;0.000000;-0.988714;,
  0.149819;0.000001;-0.988714;,
  -0.117088;0.000000;0.993122;,
  -0.117088;-0.000000;0.993122;,
  -0.853698;0.000000;-0.520768;,
  -0.853698;0.000000;-0.520768;,
  -0.853698;0.000000;-0.520768;,
  0.000000;1.000000;0.000000;,
  0.836040;0.000000;0.548669;,
  0.836040;-0.000001;0.548668;,
  0.836039;-0.000001;0.548671;,
  0.836044;0.000000;0.548662;,
  0.363188;-0.916196;-0.169351;,
  0.906319;0.000001;0.422595;,
  0.730618;0.000001;0.682786;,
  -0.853698;-0.000000;0.520768;,
  -0.853698;-0.000000;0.520768;,
  0.836044;0.000000;-0.548662;,
  0.836043;-0.000001;-0.548664;,
  0.149813;0.000000;0.988714;,
  0.149813;0.000000;0.988714;,
  -0.117087;0.000000;-0.993122;,
  -0.117087;-0.000000;-0.993122;,
  -0.117088;-0.000000;-0.993122;,
  -0.117089;0.000000;-0.993121;,
  0.259590;-0.958103;0.121042;;
  78;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;19,19,19,19;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  3;4,6,14;,
  3;6,11,14;,
  3;14,11,3;,
  3;11,5,3;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;7,41,8;,
  3;8,41,16;,
  3;41,42,16;,
  3;42,9,16;,
  4;15,15,10,10;,
  3;43,44,20;,
  3;20,44,4;,
  3;44,6,4;,
  3;45,12,46;,
  3;46,12,18;,
  3;12,13,18;,
  3;9,42,47;,
  3;42,48,47;,
  3;48,49,47;,
  3;1,1,1;,
  3;1,1,1;,
  3;50,1,1;,
  3;1,1,1;,
  3;51,52,53;,
  3;53,52,17;,
  3;52,54,17;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;55,15,15,55;,
  4;19,19,15,55;,
  4;10,15,19,19;,
  4;55,15,19,19;,
  4;19,19,15,10;,
  3;24,29,22;,
  3;22,29,36;,
  3;29,23,36;,
  3;23,21,36;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;25,56,26;,
  3;26,56,38;,
  3;56,57,38;,
  3;57,27,38;,
  4;19,37,35,19;,
  3;28,58,59;,
  3;58,24,59;,
  3;24,22,59;,
  3;60,61,34;,
  3;61,30,34;,
  3;30,31,34;,
  3;57,62,27;,
  3;27,62,33;,
  3;62,63,33;,
  3;1,1,1;,
  3;1,50,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;64,65,32;,
  3;65,66,32;,
  3;66,67,32;,
  4;19,19,19,19;,
  4;37,37,35,35;,
  4;37,19,19,35;,
  4;68,37,19,19;,
  4;68,37,37,68;,
  4;19,19,37,68;,
  4;19,19,19,19;;
 }
 MeshTextureCoords {
  92;
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.500000;,
  0.500000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.500000;0.875000;,
  0.500000;0.812500;,
  0.625000;0.812500;,
  0.625000;0.875000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.687500;0.000000;,
  0.250000;0.250000;,
  0.312500;0.000000;,
  0.250000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.812500;0.000000;,
  0.375000;0.375000;,
  0.125000;0.250000;,
  0.187500;0.000000;,
  0.125000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.937500;,
  0.625000;0.937500;,
  0.625000;1.000000;,
  0.375000;0.937500;,
  0.375000;1.000000;,
  0.375000;0.812500;,
  0.375000;0.875000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.937500;,
  0.625000;0.937500;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.687500;0.000000;,
  0.312500;0.000000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  0.375000;0.375000;,
  0.187500;0.000000;,
  0.125000;0.250000;,
  0.125000;0.000000;,
  0.500000;0.812500;,
  0.625000;0.812500;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.375000;0.937500;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.375000;0.812500;;
 }
}
