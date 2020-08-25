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
 164;
 -13.31383;20.93497;-8.65573;,
 -13.31383;-14.52440;-8.65573;,
 -15.86897;-14.52440;0.04691;,
 -15.86897;20.93497;0.04691;,
 -6.45922;20.93497;-14.59506;,
 -6.45922;-14.52440;-14.59505;,
 2.51841;20.93497;-15.88579;,
 2.51841;-14.52440;-15.88579;,
 10.76866;20.93497;-12.11808;,
 10.76866;-14.52440;-12.11807;,
 15.67200;20.93497;-4.48788;,
 15.67200;-14.52440;-4.48787;,
 15.67200;20.93497;4.58169;,
 15.67200;-14.52440;4.58170;,
 10.76866;20.93497;12.21189;,
 10.76866;-14.52440;12.21189;,
 2.51841;20.93497;15.97961;,
 2.51841;-14.52440;15.97961;,
 -6.45922;20.93497;14.68887;,
 -6.45922;-14.52440;14.68888;,
 -13.31383;20.93497;8.74955;,
 -13.31383;-14.52440;8.74955;,
 -15.86897;20.93497;0.04691;,
 -15.86897;-14.52440;0.04691;,
 -15.86897;24.09397;0.04691;,
 -15.86897;34.11691;0.04691;,
 -13.31383;34.11691;-8.65574;,
 -13.31383;24.09397;-8.65573;,
 0.22773;34.11691;0.04691;,
 -6.45922;34.11691;-14.59506;,
 -6.45922;24.09397;-14.59506;,
 0.22773;34.11691;0.04691;,
 2.51841;34.11691;-15.88580;,
 2.51841;24.09397;-15.88579;,
 0.22773;34.11691;0.04691;,
 10.76866;34.11691;-12.11808;,
 10.76866;24.09397;-12.11808;,
 0.22773;34.11691;0.04691;,
 15.67200;34.11691;-4.48788;,
 15.67200;24.09397;-4.48788;,
 0.22773;34.11691;0.04691;,
 15.67200;34.11691;4.58169;,
 15.67200;24.09397;4.58169;,
 0.22773;34.11691;0.04691;,
 10.76866;34.11691;12.21189;,
 10.76866;24.09397;12.21189;,
 0.22773;34.11691;0.04691;,
 2.51841;34.11691;15.97960;,
 2.51841;24.09397;15.97961;,
 0.22773;34.11691;0.04691;,
 -6.45922;34.11691;14.68887;,
 -6.45922;24.09397;14.68887;,
 0.22773;34.11691;0.04691;,
 -13.31383;34.11691;8.74955;,
 -13.31383;24.09397;8.74955;,
 0.22773;34.11691;0.04691;,
 -15.86897;34.11691;0.04691;,
 -15.86897;24.09397;0.04691;,
 0.22773;34.11691;0.04691;,
 -15.17116;20.93497;0.04691;,
 -12.72658;20.93497;-8.27827;,
 -12.72658;24.09397;-8.27827;,
 -15.17116;24.09397;0.04691;,
 -6.16924;20.93497;-13.96002;,
 -6.16924;24.09397;-13.96002;,
 2.41918;20.93497;-15.19486;,
 2.41918;24.09397;-15.19486;,
 10.31142;20.93497;-11.59077;,
 10.31142;24.09397;-11.59077;,
 15.00253;20.93497;-4.29145;,
 15.00253;24.09397;-4.29145;,
 15.00253;20.93497;4.38527;,
 15.00253;24.09397;4.38527;,
 10.31142;20.93497;11.68458;,
 10.31142;24.09397;11.68458;,
 2.41918;20.93497;15.28868;,
 2.41918;24.09397;15.28868;,
 -6.16924;20.93497;14.05383;,
 -6.16924;24.09397;14.05383;,
 -12.72658;20.93497;8.37209;,
 -12.72658;24.09397;8.37209;,
 -15.17116;20.93497;0.04691;,
 -15.17116;24.09397;0.04691;,
 -11.14182;41.21413;-7.22528;,
 -8.24486;21.36913;-5.31772;,
 -9.81991;21.36913;0.04691;,
 -13.27698;41.21413;0.04691;,
 -5.41391;41.21413;-12.18855;,
 -4.01950;21.36913;-8.97892;,
 2.08829;41.21412;-13.26707;,
 1.51482;21.36913;-9.77475;,
 8.98261;41.21412;-10.11859;,
 6.60040;21.36913;-7.45207;,
 13.08000;41.21412;-3.74268;,
 9.62332;21.36913;-2.74881;,
 13.08000;41.21413;3.83649;,
 9.62332;21.36913;2.84262;,
 8.98261;41.21413;10.21240;,
 6.60040;21.36913;7.54589;,
 2.08829;41.21413;13.36088;,
 1.51482;21.36913;9.86856;,
 -5.41391;41.21413;12.28236;,
 -4.01950;21.36913;9.07274;,
 -11.14182;41.21413;7.31909;,
 -8.24486;21.36913;5.41154;,
 -13.27698;41.21413;0.04691;,
 -9.81991;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.10258;21.36913;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 0.17387;41.21413;0.04691;,
 -12.36127;-24.46675;-8.02838;,
 -14.73214;-24.46675;0.04691;,
 -6.00076;-24.46675;-13.53962;,
 2.32967;-24.46675;-14.73721;,
 9.98539;-24.46675;-11.24125;,
 14.53516;-24.46675;-4.16104;,
 14.53516;-24.46675;4.25486;,
 9.98539;-24.46675;11.33507;,
 2.32967;-24.46675;14.83103;,
 -6.00076;-24.46675;13.63344;,
 -12.36127;-24.46675;8.12220;,
 -14.73214;-24.46675;0.04691;,
 -7.77141;-36.41546;-5.00587;,
 -9.25534;-36.41545;0.04691;,
 0.09084;-40.74126;0.04691;,
 -3.79149;-36.41546;-8.45444;,
 0.09084;-40.74126;0.04691;,
 1.42086;-36.41547;-9.20410;,
 0.09084;-40.74126;0.04691;,
 6.21119;-36.41547;-7.01629;,
 0.09084;-40.74126;0.04691;,
 9.05834;-36.41547;-2.58640;,
 0.09084;-40.74126;0.04691;,
 9.05834;-36.41546;2.68022;,
 0.09084;-40.74126;0.04691;,
 6.21119;-36.41546;7.11011;,
 0.09084;-40.74126;0.04691;,
 1.42086;-36.41546;9.29792;,
 0.09084;-40.74126;0.04691;,
 -3.79149;-36.41545;8.54867;,
 0.09084;-40.74126;0.04691;,
 -7.77141;-36.41545;5.09969;,
 0.09084;-40.74126;0.04691;,
 -9.25534;-36.41545;0.04691;,
 0.09084;-40.74126;0.04691;;
 
 220;
 3;0,1,2;,
 3;3,0,2;,
 3;4,5,1;,
 3;0,4,1;,
 3;6,7,5;,
 3;4,6,5;,
 3;8,9,7;,
 3;6,8,7;,
 3;10,11,9;,
 3;8,10,9;,
 3;12,13,11;,
 3;10,12,11;,
 3;14,15,13;,
 3;12,14,13;,
 3;16,17,15;,
 3;14,16,15;,
 3;18,19,17;,
 3;16,18,17;,
 3;20,21,19;,
 3;18,20,19;,
 3;22,23,21;,
 3;20,22,21;,
 3;24,25,26;,
 3;27,24,26;,
 3;26,25,28;,
 3;27,26,29;,
 3;30,27,29;,
 3;29,26,31;,
 3;30,29,32;,
 3;33,30,32;,
 3;32,29,34;,
 3;33,32,35;,
 3;36,33,35;,
 3;35,32,37;,
 3;36,35,38;,
 3;39,36,38;,
 3;38,35,40;,
 3;39,38,41;,
 3;42,39,41;,
 3;41,38,43;,
 3;42,41,44;,
 3;45,42,44;,
 3;44,41,46;,
 3;45,44,47;,
 3;48,45,47;,
 3;47,44,49;,
 3;48,47,50;,
 3;51,48,50;,
 3;50,47,52;,
 3;51,50,53;,
 3;54,51,53;,
 3;53,50,55;,
 3;54,53,56;,
 3;57,54,56;,
 3;56,53,58;,
 3;3,59,60;,
 3;0,3,60;,
 3;27,61,62;,
 3;24,27,62;,
 3;61,60,59;,
 3;62,61,59;,
 3;0,60,63;,
 3;4,0,63;,
 3;30,64,61;,
 3;27,30,61;,
 3;64,63,60;,
 3;61,64,60;,
 3;4,63,65;,
 3;6,4,65;,
 3;33,66,64;,
 3;30,33,64;,
 3;66,65,63;,
 3;64,66,63;,
 3;6,65,67;,
 3;8,6,67;,
 3;36,68,66;,
 3;33,36,66;,
 3;68,67,65;,
 3;66,68,65;,
 3;8,67,69;,
 3;10,8,69;,
 3;39,70,68;,
 3;36,39,68;,
 3;70,69,67;,
 3;68,70,67;,
 3;10,69,71;,
 3;12,10,71;,
 3;42,72,70;,
 3;39,42,70;,
 3;72,71,69;,
 3;70,72,69;,
 3;12,71,73;,
 3;14,12,73;,
 3;45,74,72;,
 3;42,45,72;,
 3;74,73,71;,
 3;72,74,71;,
 3;14,73,75;,
 3;16,14,75;,
 3;48,76,74;,
 3;45,48,74;,
 3;76,75,73;,
 3;74,76,73;,
 3;16,75,77;,
 3;18,16,77;,
 3;51,78,76;,
 3;48,51,76;,
 3;78,77,75;,
 3;76,78,75;,
 3;18,77,79;,
 3;20,18,79;,
 3;54,80,78;,
 3;51,54,78;,
 3;80,79,77;,
 3;78,80,77;,
 3;20,79,81;,
 3;22,20,81;,
 3;57,82,80;,
 3;54,57,80;,
 3;82,81,79;,
 3;80,82,79;,
 3;83,84,85;,
 3;86,83,85;,
 3;87,88,84;,
 3;83,87,84;,
 3;89,90,88;,
 3;87,89,88;,
 3;91,92,90;,
 3;89,91,90;,
 3;93,94,92;,
 3;91,93,92;,
 3;95,96,94;,
 3;93,95,94;,
 3;97,98,96;,
 3;95,97,96;,
 3;99,100,98;,
 3;97,99,98;,
 3;101,102,100;,
 3;99,101,100;,
 3;103,104,102;,
 3;101,103,102;,
 3;105,106,104;,
 3;103,105,104;,
 3;85,84,107;,
 3;84,88,108;,
 3;88,90,109;,
 3;90,92,110;,
 3;92,94,111;,
 3;94,96,112;,
 3;96,98,113;,
 3;98,100,114;,
 3;100,102,115;,
 3;102,104,116;,
 3;104,106,117;,
 3;83,86,118;,
 3;87,83,119;,
 3;89,87,120;,
 3;91,89,121;,
 3;93,91,122;,
 3;95,93,123;,
 3;97,95,124;,
 3;99,97,125;,
 3;101,99,126;,
 3;103,101,127;,
 3;105,103,128;,
 3;1,129,130;,
 3;2,1,130;,
 3;5,131,129;,
 3;1,5,129;,
 3;7,132,131;,
 3;5,7,131;,
 3;9,133,132;,
 3;7,9,132;,
 3;11,134,133;,
 3;9,11,133;,
 3;13,135,134;,
 3;11,13,134;,
 3;15,136,135;,
 3;13,15,135;,
 3;17,137,136;,
 3;15,17,136;,
 3;19,138,137;,
 3;17,19,137;,
 3;21,139,138;,
 3;19,21,138;,
 3;23,140,139;,
 3;21,23,139;,
 3;129,141,142;,
 3;130,129,142;,
 3;142,141,143;,
 3;131,144,141;,
 3;129,131,141;,
 3;141,144,145;,
 3;132,146,144;,
 3;131,132,144;,
 3;144,146,147;,
 3;133,148,146;,
 3;132,133,146;,
 3;146,148,149;,
 3;134,150,148;,
 3;133,134,148;,
 3;148,150,151;,
 3;135,152,150;,
 3;134,135,150;,
 3;150,152,153;,
 3;136,154,152;,
 3;135,136,152;,
 3;152,154,155;,
 3;137,156,154;,
 3;136,137,154;,
 3;154,156,157;,
 3;138,158,156;,
 3;137,138,156;,
 3;156,158,159;,
 3;139,160,158;,
 3;138,139,158;,
 3;158,160,161;,
 3;140,162,160;,
 3;139,140,160;,
 3;160,162,163;;
 
 MeshMaterialList {
  1;
  220;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.589804;0.000000;1.000000;;
   5.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  133;
  -0.889920;-0.000000;-0.456117;,
  -0.839729;-0.057030;-0.540002;,
  -0.998379;-0.056906;-0.000294;,
  -0.995245;0.000000;0.097403;,
  -0.502034;-0.000000;-0.864848;,
  -0.414454;-0.057482;-0.908253;,
  0.045222;-0.000000;-0.998977;,
  0.142369;-0.058128;-0.988105;,
  0.578133;-0.000000;-0.815942;,
  0.653965;-0.058747;-0.754241;,
  0.927493;-0.000000;-0.373840;,
  0.957905;-0.059156;-0.280924;,
  0.982375;0.000000;0.186920;,
  0.957723;-0.059222;0.281531;,
  0.725376;0.000000;0.688353;,
  0.653491;-0.058917;0.754638;,
  0.238055;0.000000;0.971252;,
  0.141755;-0.058352;0.988180;,
  -0.324823;0.000000;0.945775;,
  -0.414991;-0.057691;0.907995;,
  -0.784585;0.000000;0.620022;,
  -0.840041;-0.057152;0.539504;,
  -0.995245;-0.000000;-0.097403;,
  -0.995245;0.000000;0.097403;,
  -0.889920;-0.000000;-0.456117;,
  -0.784585;-0.000000;-0.620022;,
  0.000000;1.000000;-0.000000;,
  -0.502034;-0.000000;-0.864848;,
  -0.324823;-0.000000;-0.945775;,
  0.045222;-0.000000;-0.998977;,
  0.238055;-0.000000;-0.971252;,
  0.578133;-0.000000;-0.815942;,
  0.725376;-0.000000;-0.688353;,
  0.927493;-0.000000;-0.373840;,
  0.982375;-0.000000;-0.186920;,
  0.982375;0.000000;0.186920;,
  0.927493;0.000000;0.373840;,
  0.725376;0.000000;0.688353;,
  0.578133;0.000000;0.815942;,
  0.238055;0.000000;0.971252;,
  0.045222;0.000000;0.998977;,
  -0.324823;0.000000;0.945775;,
  -0.502034;0.000000;0.864848;,
  -0.784585;0.000000;0.620022;,
  -0.889920;0.000000;0.456117;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.876797;-0.171188;-0.449356;,
  -0.772974;-0.171552;-0.610803;,
  -0.980616;-0.170826;-0.095971;,
  -0.980616;-0.170826;0.095969;,
  -0.494544;-0.172523;-0.851858;,
  -0.319960;-0.173130;-0.931478;,
  0.044482;-0.174395;-0.983671;,
  0.234340;-0.175059;-0.956263;,
  0.569064;-0.176230;-0.803187;,
  0.713923;-0.176733;-0.677554;,
  0.912763;-0.177422;-0.367946;,
  0.966750;-0.177606;-0.183983;,
  0.966754;-0.177606;0.183963;,
  0.912763;-0.177424;0.367946;,
  0.713915;-0.176735;0.677562;,
  0.569047;-0.176228;0.803199;,
  0.234351;-0.175058;0.956261;,
  0.044492;-0.174396;0.983670;,
  -0.319964;-0.173131;0.931477;,
  -0.494554;-0.172522;0.851852;,
  -0.772973;-0.171552;0.610805;,
  -0.876795;-0.171189;0.449360;,
  0.000000;1.000000;-0.000000;,
  -0.808019;-0.269622;-0.523841;,
  -0.963139;-0.268975;-0.003872;,
  -0.396295;-0.271618;-0.877026;,
  0.140703;-0.274315;-0.951291;,
  0.632290;-0.276878;-0.723566;,
  0.922693;-0.278475;-0.266626;,
  0.920312;-0.278614;0.274590;,
  0.625981;-0.277268;0.728883;,
  0.132687;-0.274829;0.952294;,
  -0.403450;-0.272077;0.873615;,
  -0.812187;-0.269908;0.517207;,
  -0.603656;-0.655031;-0.454460;,
  -0.754178;-0.654272;-0.056066;,
  -0.000002;-1.000000;-0.000002;,
  -0.261735;-0.656658;-0.707316;,
  0.161802;-0.658648;-0.734849;,
  0.532363;-0.660357;-0.529640;,
  0.733439;-0.661249;-0.157536;,
  0.702300;-0.661058;0.264152;,
  0.448569;-0.659834;0.602831;,
  0.051530;-0.657951;0.751296;,
  -0.363670;-0.656025;0.661343;,
  -0.664526;-0.654642;0.360345;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.889911;-0.000000;-0.456134;,
  -0.784579;0.000000;-0.620029;,
  -0.995244;-0.000000;-0.097413;,
  -0.995244;0.000000;0.097413;,
  -0.502036;0.000000;-0.864847;,
  -0.324827;0.000000;-0.945773;,
  0.045213;0.000000;-0.998977;,
  0.238044;0.000000;-0.971254;,
  0.578116;0.000000;-0.815955;,
  0.725354;0.000000;-0.688376;,
  0.927483;0.000000;-0.373865;,
  0.982373;0.000000;-0.186932;,
  0.982373;0.000000;0.186932;,
  0.927483;0.000000;0.373865;,
  0.725354;0.000000;0.688376;,
  0.578116;0.000000;0.815955;,
  0.238045;0.000000;0.971254;,
  0.045213;0.000000;0.998977;,
  -0.324827;0.000000;0.945773;,
  -0.502036;0.000000;0.864847;,
  -0.784579;0.000000;0.620029;,
  -0.889911;0.000000;0.456134;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;;
  220;
  3;0,1,2;,
  3;3,0,2;,
  3;4,5,1;,
  3;0,4,1;,
  3;6,7,5;,
  3;4,6,5;,
  3;8,9,7;,
  3;6,8,7;,
  3;10,11,9;,
  3;8,10,9;,
  3;12,13,11;,
  3;10,12,11;,
  3;14,15,13;,
  3;12,14,13;,
  3;16,17,15;,
  3;14,16,15;,
  3;18,19,17;,
  3;16,18,17;,
  3;20,21,19;,
  3;18,20,19;,
  3;3,2,21;,
  3;20,3,21;,
  3;22,23,24;,
  3;25,22,24;,
  3;45,93,26;,
  3;25,24,27;,
  3;28,25,27;,
  3;94,45,26;,
  3;28,27,29;,
  3;30,28,29;,
  3;95,94,26;,
  3;30,29,31;,
  3;32,30,31;,
  3;96,95,26;,
  3;32,31,33;,
  3;34,32,33;,
  3;97,96,26;,
  3;34,33,35;,
  3;36,34,35;,
  3;98,97,26;,
  3;36,35,37;,
  3;38,36,37;,
  3;45,98,26;,
  3;38,37,39;,
  3;40,38,39;,
  3;99,45,26;,
  3;40,39,41;,
  3;42,40,41;,
  3;100,99,26;,
  3;42,41,43;,
  3;44,42,43;,
  3;101,100,26;,
  3;44,43,23;,
  3;22,44,23;,
  3;93,101,26;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;102,103,104;,
  3;105,102,104;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;106,107,103;,
  3;102,106,103;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;108,109,107;,
  3;106,108,107;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;110,111,109;,
  3;108,110,109;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;112,113,111;,
  3;110,112,111;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;114,115,113;,
  3;112,114,113;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;116,117,115;,
  3;114,116,115;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;118,119,117;,
  3;116,118,117;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;120,121,119;,
  3;118,120,119;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;122,123,121;,
  3;120,122,121;,
  3;45,45,45;,
  3;45,45,45;,
  3;46,46,46;,
  3;46,46,46;,
  3;105,104,123;,
  3;122,105,123;,
  3;47,48,49;,
  3;50,47,49;,
  3;51,52,48;,
  3;47,51,48;,
  3;53,54,52;,
  3;51,53,52;,
  3;55,56,54;,
  3;53,55,54;,
  3;57,58,56;,
  3;55,57,56;,
  3;59,60,58;,
  3;57,59,58;,
  3;61,62,60;,
  3;59,61,60;,
  3;63,64,62;,
  3;61,63,62;,
  3;65,66,64;,
  3;63,65,64;,
  3;67,68,66;,
  3;65,67,66;,
  3;50,49,68;,
  3;67,50,68;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;46,46,46;,
  3;45,124,69;,
  3;125,45,69;,
  3;126,125,69;,
  3;127,126,69;,
  3;128,127,69;,
  3;129,128,69;,
  3;45,129,69;,
  3;130,45,69;,
  3;131,130,69;,
  3;132,131,69;,
  3;124,132,69;,
  3;1,70,71;,
  3;2,1,71;,
  3;5,72,70;,
  3;1,5,70;,
  3;7,73,72;,
  3;5,7,72;,
  3;9,74,73;,
  3;7,9,73;,
  3;11,75,74;,
  3;9,11,74;,
  3;13,76,75;,
  3;11,13,75;,
  3;15,77,76;,
  3;13,15,76;,
  3;17,78,77;,
  3;15,17,77;,
  3;19,79,78;,
  3;17,19,78;,
  3;21,80,79;,
  3;19,21,79;,
  3;2,71,80;,
  3;21,2,80;,
  3;70,81,82;,
  3;71,70,82;,
  3;82,81,83;,
  3;72,84,81;,
  3;70,72,81;,
  3;81,84,83;,
  3;73,85,84;,
  3;72,73,84;,
  3;84,85,83;,
  3;74,86,85;,
  3;73,74,85;,
  3;85,86,83;,
  3;75,87,86;,
  3;74,75,86;,
  3;86,87,83;,
  3;76,88,87;,
  3;75,76,87;,
  3;87,88,83;,
  3;77,89,88;,
  3;76,77,88;,
  3;88,89,83;,
  3;78,90,89;,
  3;77,78,89;,
  3;89,90,83;,
  3;79,91,90;,
  3;78,79,90;,
  3;90,91,83;,
  3;80,92,91;,
  3;79,80,91;,
  3;91,92,83;,
  3;71,82,92;,
  3;80,71,92;,
  3;92,82,83;;
 }
 MeshTextureCoords {
  164;
  0.090909;1.000000;,
  0.090909;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.181818;1.000000;,
  0.181818;1.000000;,
  0.272727;1.000000;,
  0.272727;1.000000;,
  0.363636;1.000000;,
  0.363636;1.000000;,
  0.454545;1.000000;,
  0.454545;1.000000;,
  0.545455;1.000000;,
  0.545455;1.000000;,
  0.636364;1.000000;,
  0.636364;1.000000;,
  0.727273;1.000000;,
  0.727273;1.000000;,
  0.818182;1.000000;,
  0.818182;1.000000;,
  0.909091;1.000000;,
  0.909091;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.090909;0.000000;,
  0.090909;0.000000;,
  0.045455;0.000000;,
  0.181818;0.000000;,
  0.181818;0.000000;,
  0.136364;0.000000;,
  0.272727;0.000000;,
  0.272727;0.000000;,
  0.227273;0.000000;,
  0.363636;0.000000;,
  0.363636;0.000000;,
  0.318182;0.000000;,
  0.454545;0.000000;,
  0.454545;0.000000;,
  0.409091;0.000000;,
  0.545455;0.000000;,
  0.545455;0.000000;,
  0.500000;0.000000;,
  0.636364;0.000000;,
  0.636364;0.000000;,
  0.590909;0.000000;,
  0.727273;0.000000;,
  0.727273;0.000000;,
  0.681818;0.000000;,
  0.818182;0.000000;,
  0.818182;0.000000;,
  0.772727;0.000000;,
  0.909091;0.000000;,
  0.909091;0.000000;,
  0.863636;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.954546;0.000000;,
  0.000000;1.000000;,
  0.090909;1.000000;,
  0.090909;0.000000;,
  0.000000;0.000000;,
  0.181818;1.000000;,
  0.181818;0.000000;,
  0.272727;1.000000;,
  0.272727;0.000000;,
  0.363636;1.000000;,
  0.363636;0.000000;,
  0.454545;1.000000;,
  0.454545;0.000000;,
  0.545455;1.000000;,
  0.545455;0.000000;,
  0.636364;1.000000;,
  0.636364;0.000000;,
  0.727273;1.000000;,
  0.727273;0.000000;,
  0.818182;1.000000;,
  0.818182;0.000000;,
  0.909091;1.000000;,
  0.909091;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.090909;0.000000;,
  0.090909;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.181818;0.000000;,
  0.181818;1.000000;,
  0.272727;0.000000;,
  0.272727;1.000000;,
  0.363636;0.000000;,
  0.363636;1.000000;,
  0.454545;0.000000;,
  0.454545;1.000000;,
  0.545455;0.000000;,
  0.545455;1.000000;,
  0.636364;0.000000;,
  0.636364;1.000000;,
  0.727273;0.000000;,
  0.727273;1.000000;,
  0.818182;0.000000;,
  0.818182;1.000000;,
  0.909091;0.000000;,
  0.909091;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.045455;1.000000;,
  0.136364;1.000000;,
  0.227273;1.000000;,
  0.318182;1.000000;,
  0.409091;1.000000;,
  0.500000;1.000000;,
  0.590909;1.000000;,
  0.681818;1.000000;,
  0.772727;1.000000;,
  0.863636;1.000000;,
  0.954546;1.000000;,
  0.045455;0.000000;,
  0.136364;0.000000;,
  0.227273;0.000000;,
  0.318182;0.000000;,
  0.409091;0.000000;,
  0.500000;0.000000;,
  0.590909;0.000000;,
  0.681818;0.000000;,
  0.772727;0.000000;,
  0.863636;0.000000;,
  0.954546;0.000000;,
  0.090909;1.000000;,
  0.000000;1.000000;,
  0.181818;1.000000;,
  0.272727;1.000000;,
  0.363636;1.000000;,
  0.454545;1.000000;,
  0.545455;1.000000;,
  0.636364;1.000000;,
  0.727273;1.000000;,
  0.818182;1.000000;,
  0.909091;1.000000;,
  1.000000;1.000000;,
  0.090909;1.000000;,
  0.000000;1.000000;,
  0.045455;1.000000;,
  0.181818;1.000000;,
  0.136364;1.000000;,
  0.272727;1.000000;,
  0.227273;1.000000;,
  0.363636;1.000000;,
  0.318182;1.000000;,
  0.454545;1.000000;,
  0.409091;1.000000;,
  0.545455;1.000000;,
  0.500000;1.000000;,
  0.636364;1.000000;,
  0.590909;1.000000;,
  0.727273;1.000000;,
  0.681818;1.000000;,
  0.818182;1.000000;,
  0.772727;1.000000;,
  0.909091;1.000000;,
  0.863636;1.000000;,
  1.000000;1.000000;,
  0.954546;1.000000;;
 }
}
