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
 175;
 6.55511;-10.64011;2.60478;,
 4.03385;-8.59531;2.60478;,
 5.29448;-11.44399;1.22586;,
 6.55511;-11.44399;1.22586;,
 4.03385;-10.64011;-0.15306;,
 5.29448;-11.44399;-0.15306;,
 6.55511;-8.59531;3.54225;,
 2.85980;-8.59531;-0.15306;,
 6.55511;-11.77623;-0.15306;,
 7.81576;-11.44399;1.22586;,
 9.07639;-8.59531;2.60478;,
 5.29448;-11.44399;-1.42647;,
 4.03385;-8.59531;-2.69986;,
 7.81576;-11.44399;-0.15306;,
 6.55511;-11.44399;-1.42646;,
 7.81576;-11.44399;-1.42647;,
 9.07639;-10.64011;-0.15306;,
 6.55511;-10.64011;-2.69987;,
 9.07639;-8.59531;-2.69987;,
 10.25043;-8.59531;-0.15306;,
 6.55511;-8.59531;-3.84838;,
 8.12485;5.23627;4.05915;,
 -0.52585;5.71536;4.05915;,
 -0.52585;-0.43528;5.19079;,
 9.63890;-0.43528;5.19079;,
 9.18803;-3.40164;3.19377;,
 8.33784;-3.55692;4.10557;,
 8.88430;-3.14927;3.19377;,
 10.34348;-4.70455;3.19377;,
 9.39149;-5.07661;3.19377;,
 12.52751;-4.50387;-0.16958;,
 13.59883;-4.73805;-0.16958;,
 11.45620;-0.43528;2.51416;,
 9.72137;-1.32910;5.19079;,
 11.45620;-1.32910;2.51416;,
 -0.52585;7.84596;1.06806;,
 -0.52585;5.71536;4.05915;,
 8.90284;7.10004;1.06806;,
 11.40712;-3.57294;-0.16958;,
 9.39149;-5.07661;-3.53291;,
 10.34348;-4.70455;-3.53291;,
 8.88430;-3.14927;-3.53291;,
 8.33784;-3.55692;-4.44473;,
 9.18803;-3.40164;-3.53291;,
 14.19233;-0.43528;-0.16248;,
 15.26041;-1.32910;-0.16248;,
 -0.52585;9.32489;-0.16248;,
 11.45620;8.56732;-0.16248;,
 -0.52585;-0.43528;-5.51575;,
 -0.52585;5.71536;-4.38411;,
 8.12485;5.23627;-4.38412;,
 9.63890;-0.43528;-5.51576;,
 8.90284;7.10004;-1.39301;,
 -0.52585;7.84596;-1.39301;,
 -0.52585;5.71536;-4.38411;,
 11.45620;-0.43528;-2.83911;,
 11.45620;-1.32910;-2.83911;,
 9.72137;-1.32910;-5.51576;,
 4.03385;-8.59531;2.60478;,
 6.55511;-8.59531;3.54225;,
 6.55511;-7.07155;2.96292;,
 4.42912;-7.07155;2.17243;,
 4.42912;-7.07155;2.17243;,
 3.43913;-7.07155;-0.15306;,
 9.07639;-8.59531;2.60478;,
 8.68112;-7.07155;2.17243;,
 4.42912;-7.07155;-2.30060;,
 6.55511;-3.43738;3.54225;,
 4.03385;-3.43738;2.60478;,
 4.03385;-3.43738;2.60478;,
 2.85980;-3.43738;-0.15306;,
 -0.52585;-1.32910;5.19079;,
 -0.52585;-0.43528;5.19079;,
 -0.52585;-0.43528;-5.51575;,
 -0.52585;-1.32910;-5.51575;,
 -0.52585;-1.32910;5.19079;,
 9.07639;-3.43738;2.60478;,
 4.03385;-3.43738;-2.69986;,
 2.85980;-1.32910;-0.15306;,
 4.03385;-1.32910;2.60478;,
 4.03385;-1.32910;2.60478;,
 6.55511;-1.32910;3.54225;,
 10.25043;-8.59531;-0.15306;,
 9.67111;-7.07155;-0.15306;,
 6.55511;-7.07155;-3.26904;,
 6.55511;-8.59531;-3.84838;,
 4.03385;-8.59531;-2.69986;,
 4.42912;-7.07155;-2.30060;,
 7.46717;-1.32910;4.10557;,
 8.33784;-3.55692;4.10557;,
 9.54793;-3.08398;4.10557;,
 8.86208;-1.32910;4.10557;,
 8.17294;-1.32910;3.19377;,
 7.46717;-1.32910;4.10557;,
 4.03385;-1.32910;-2.69986;,
 9.07639;-8.59531;-2.69987;,
 8.68112;-7.07155;-2.30060;,
 10.25043;-3.43738;-0.15306;,
 6.55511;-3.43738;-3.84838;,
 4.03385;-3.43738;-2.69986;,
 9.07639;-3.43738;-2.69987;,
 6.55511;-1.32910;-3.84838;,
 4.03385;-1.32910;-2.69986;,
 13.68581;-3.12655;-0.16958;,
 12.98333;-1.32910;-0.16958;,
 9.54793;-3.08398;4.10557;,
 9.74864;-3.18255;3.19377;,
 13.68581;-3.12655;-0.16958;,
 12.90208;-2.95523;-0.16958;,
 7.92688;-1.32910;3.19377;,
 8.10247;-1.32910;2.96691;,
 9.07639;-3.10389;2.60478;,
 9.86096;-1.32910;0.76180;,
 10.62380;-1.32910;-0.16958;,
 9.75232;-1.32910;-1.23362;,
 10.62380;-1.32910;-0.16958;,
 9.86096;-1.32910;0.76180;,
 10.25043;-1.32910;-0.15306;,
 9.75232;-1.32910;-1.23362;,
 9.07639;-2.62051;-2.69987;,
 8.29681;-1.32910;-3.05499;,
 7.92688;-1.32910;-3.53291;,
 -0.52585;-1.32910;-5.51575;,
 7.46717;-1.32910;-4.44473;,
 8.17294;-1.32910;-3.53291;,
 9.54793;-3.08398;-4.44473;,
 9.74864;-3.18255;-3.53291;,
 8.86208;-1.32910;-4.44473;,
 9.54793;-3.08398;-4.44473;,
 8.33784;-3.55692;-4.44473;,
 7.46717;-1.32910;-4.44473;,
 9.07639;-3.10389;2.60478;,
 8.10247;-1.32910;2.96691;,
 10.34348;-4.70455;3.19377;,
 13.59883;-4.73805;-0.16958;,
 12.90208;-2.95523;-0.16958;,
 9.74864;-3.18255;3.19377;,
 8.29681;-1.32910;-3.05499;,
 9.07639;-2.62051;-2.69987;,
 10.34348;-4.70455;-3.53291;,
 9.74864;-3.18255;-3.53291;,
 10.25043;-1.32910;-0.15306;,
 9.86096;-1.32910;0.76180;,
 9.75232;-1.32910;-1.23362;,
 9.39149;-5.07661;3.19377;,
 9.18803;-3.40164;3.19377;,
 8.88430;-3.14927;3.19377;,
 7.92688;-1.32910;3.19377;,
 8.17294;-1.32910;3.19377;,
 7.92688;-1.32910;-3.53291;,
 8.17294;-1.32910;-3.53291;,
 9.39149;-5.07661;-3.53291;,
 8.88430;-3.14927;-3.53291;,
 9.18803;-3.40164;-3.53291;,
 2.85980;-1.32910;-0.15306;,
 4.03385;-1.32910;-2.69986;,
 12.98333;-1.32910;-0.16958;,
 8.86208;-1.32910;-4.44473;,
 11.45620;-1.32910;-2.83911;,
 6.55511;-1.32910;-3.84838;,
 9.72137;-1.32910;-5.51576;,
 8.29681;-1.32910;-3.05499;,
 7.92688;-1.32910;-3.53291;,
 8.17294;-1.32910;-3.53291;,
 7.46717;-1.32910;-4.44473;,
 4.03385;-1.32910;2.60478;,
 6.55511;-1.32910;3.54225;,
 7.46717;-1.32910;4.10557;,
 8.17294;-1.32910;3.19377;,
 8.10247;-1.32910;2.96691;,
 7.92688;-1.32910;3.19377;,
 9.72137;-1.32910;5.19079;,
 8.86208;-1.32910;4.10557;,
 11.45620;-1.32910;2.51416;,
 15.26041;-1.32910;-0.16248;;
 
 144;
 4;0,1,2,3;,
 4;2,1,4,5;,
 3;1,0,6;,
 3;1,7,4;,
 3;3,2,8;,
 3;2,5,8;,
 4;0,3,9,10;,
 4;11,5,4,12;,
 3;9,3,8;,
 3;8,5,11;,
 3;6,0,10;,
 3;12,4,7;,
 3;13,9,8;,
 3;8,11,14;,
 3;15,13,8;,
 3;14,15,8;,
 4;9,13,16,10;,
 4;17,14,11,12;,
 4;16,13,15,18;,
 4;15,14,17,18;,
 3;10,16,19;,
 3;17,12,20;,
 3;19,16,18;,
 3;18,17,20;,
 4;21,22,23,24;,
 3;25,26,27;,
 4;28,29,30,31;,
 4;32,24,33,34;,
 4;35,36,21,37;,
 3;29,38,30;,
 4;21,24,32,37;,
 3;39,30,38;,
 4;30,39,40,31;,
 3;41,42,43;,
 4;44,32,34,45;,
 4;46,35,37,47;,
 4;48,49,50,51;,
 4;52,53,46,47;,
 4;50,54,53,52;,
 4;37,32,44,47;,
 4;55,56,57,51;,
 4;56,55,44,45;,
 4;44,55,52,47;,
 4;55,51,50,52;,
 4;58,59,60,61;,
 4;62,63,7,1;,
 4;60,59,64,65;,
 4;7,63,66,12;,
 4;61,60,67,68;,
 4;69,70,63,62;,
 4;71,33,24,23;,
 4;72,73,74,75;,
 4;67,60,65,76;,
 4;63,70,77,66;,
 4;78,70,69,79;,
 4;80,68,67,81;,
 4;64,82,83,65;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,27,26,93;,
 4;94,77,70,78;,
 4;95,85,84,96;,
 4;83,82,95,96;,
 4;65,83,97,76;,
 4;98,84,87,99;,
 4;96,84,98,100;,
 4;97,83,96,100;,
 4;101,98,99,102;,
 4;91,90,103,104;,
 3;26,25,105;,
 3;105,25,106;,
 3;105,106,107;,
 3;106,108,107;,
 3;109,110,29;,
 3;110,111,29;,
 3;29,111,38;,
 3;111,112,38;,
 3;112,113,38;,
 4;114,115,116,117;,
 3;38,113,39;,
 3;113,118,39;,
 3;118,119,39;,
 3;119,120,39;,
 3;120,121,39;,
 4;57,122,48,51;,
 4;123,42,41,124;,
 3;107,108,125;,
 3;108,126,125;,
 3;126,43,125;,
 3;43,42,125;,
 4;127,128,129,130;,
 4;104,103,128,127;,
 3;76,131,67;,
 3;131,132,67;,
 3;132,81,67;,
 4;133,134,135,136;,
 3;98,101,100;,
 3;101,137,100;,
 3;137,138,100;,
 4;135,134,139,140;,
 3;97,141,76;,
 3;141,142,76;,
 3;142,131,76;,
 3;100,138,97;,
 3;138,143,97;,
 3;143,141,97;,
 3;133,136,144;,
 3;136,145,144;,
 3;144,145,146;,
 3;144,146,147;,
 3;146,148,147;,
 3;72,36,73;,
 3;36,35,73;,
 3;35,46,73;,
 3;46,53,73;,
 3;53,54,73;,
 3;149,150,151;,
 3;150,152,151;,
 3;152,153,151;,
 3;153,140,151;,
 3;140,139,151;,
 3;75,74,154;,
 3;154,74,155;,
 3;156,157,158;,
 3;155,74,159;,
 3;158,157,160;,
 3;161,159,162;,
 3;163,162,164;,
 3;162,159,164;,
 3;159,74,164;,
 3;157,164,160;,
 3;164,74,160;,
 3;75,154,165;,
 3;165,166,75;,
 3;75,166,167;,
 3;167,166,168;,
 3;166,169,170;,
 3;170,168,166;,
 3;171,75,167;,
 3;171,167,172;,
 3;171,172,173;,
 3;172,156,173;,
 3;173,156,174;,
 3;156,158,174;;
 
 MeshMaterialList {
  8;
  144;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
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
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
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
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.603922;0.054902;0.047059;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.178824;0.178824;0.178824;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.166275;0.131765;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.282353;0.090980;0.015686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.213333;0.213333;0.213333;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.345098;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   16.000000;
   0.690000;0.690000;0.690000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.109804;0.109804;0.109804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  129;
  -0.551078;-0.624135;0.553866;,
  -0.310127;-0.906142;0.287625;,
  -0.000000;-0.601718;0.798708;,
  -0.783597;-0.621181;-0.010430;,
  -0.000000;-0.890427;0.455126;,
  -0.483898;-0.875116;-0.003802;,
  -0.000000;-0.033885;0.999426;,
  -0.996576;-0.081287;-0.015153;,
  -0.000000;-0.999989;-0.004703;,
  0.310126;-0.906142;0.287625;,
  -0.307602;-0.901296;-0.305035;,
  0.551078;-0.624135;0.553867;,
  -0.551914;-0.625131;-0.551908;,
  0.483898;-0.875116;-0.003802;,
  -0.000000;-0.877197;-0.480131;,
  0.307601;-0.901297;-0.305034;,
  0.783597;-0.621181;-0.010430;,
  -0.000001;-0.619958;-0.784635;,
  0.996576;-0.081287;-0.015153;,
  -0.000001;-0.076503;-0.997069;,
  0.551913;-0.625132;-0.551908;,
  0.002517;0.094582;0.995514;,
  0.334233;0.523331;0.783845;,
  0.032888;0.549464;0.834870;,
  -0.516941;-0.622153;-0.587960;,
  -0.649673;-0.468404;-0.598768;,
  0.471176;0.162470;0.866947;,
  -0.618614;-0.572944;-0.537635;,
  -0.132665;-0.967034;-0.217358;,
  0.079044;-0.996838;-0.008151;,
  0.472570;0.021616;0.881028;,
  0.712518;0.234019;0.661479;,
  0.050617;0.732168;0.679241;,
  -0.706133;-0.370082;-0.603669;,
  0.737984;0.170944;0.652807;,
  0.079046;-0.996871;0.000000;,
  -0.665637;-0.488422;0.564244;,
  0.079044;-0.996838;0.008151;,
  -0.649677;-0.468407;0.598761;,
  -0.516944;-0.622157;0.587953;,
  0.573951;0.268578;0.773593;,
  0.395339;0.558584;0.729171;,
  0.044324;0.620765;0.782743;,
  0.334234;0.523331;-0.783844;,
  0.002516;0.094582;-0.995514;,
  0.032888;0.549465;-0.834869;,
  0.395338;0.558583;-0.729173;,
  0.050617;0.732166;-0.679243;,
  0.616190;0.297526;0.729238;,
  0.471176;0.162470;-0.866946;,
  0.472571;0.021616;-0.881027;,
  0.712517;0.234018;-0.661479;,
  0.737984;0.170943;-0.652808;,
  0.301464;0.451702;0.839693;,
  -0.000001;0.103263;0.994654;,
  -0.686887;0.104492;0.719213;,
  -0.994514;0.103547;-0.014843;,
  0.686886;0.104491;0.719214;,
  -0.701953;0.100524;-0.705094;,
  0.123276;-0.052271;0.990995;,
  -0.688304;-0.079885;0.721010;,
  -0.996764;-0.079030;-0.014724;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.785380;-0.052713;0.616766;,
  -0.703436;-0.076670;-0.706611;,
  -0.999891;0.000000;-0.014740;,
  -0.690481;0.000000;0.723351;,
  -0.000000;0.000000;1.000000;,
  0.994514;0.103547;-0.014843;,
  -0.000001;0.103610;-0.994618;,
  0.379430;0.148290;0.913260;,
  -0.755526;-0.295275;-0.584802;,
  -0.705510;0.000000;-0.708700;,
  0.701952;0.100525;-0.705094;,
  0.985574;-0.052119;-0.161022;,
  -0.000001;-0.079042;-0.996871;,
  0.611945;-0.050720;-0.789272;,
  0.150120;-0.000001;-0.988668;,
  0.693036;0.270854;0.668086;,
  -0.062907;-0.995098;-0.076308;,
  -0.746872;-0.260731;-0.611720;,
  -0.752611;-0.269160;-0.600940;,
  0.000000;-1.000000;-0.000000;,
  -0.755530;-0.295277;0.584796;,
  0.193338;-0.977625;-0.082886;,
  0.379430;0.148289;-0.913260;,
  -0.756444;-0.289375;-0.586561;,
  -0.755536;-0.295281;-0.584786;,
  0.098263;-0.994973;0.019331;,
  -0.755527;-0.295276;0.584800;,
  -0.746968;-0.297500;0.594586;,
  0.297223;-0.940081;-0.167049;,
  -0.755540;-0.295282;-0.584781;,
  -0.755521;-0.295275;0.584809;,
  -0.516946;-0.622154;0.587956;,
  -0.658522;-0.456131;0.598576;,
  0.044323;0.620759;-0.782747;,
  0.301462;0.451698;-0.839696;,
  0.573948;0.268577;-0.773596;,
  0.616188;0.297525;-0.729240;,
  -0.644812;0.358766;0.674911;,
  0.644811;0.358765;0.674912;,
  -0.661975;0.345944;-0.664915;,
  0.661974;0.345945;-0.664915;,
  0.358207;-0.916533;0.177919;,
  0.358198;-0.916536;0.177923;,
  0.283641;-0.944705;0.164558;,
  -0.098938;-0.994796;0.024330;,
  -0.753594;-0.284169;0.592743;,
  -0.738158;-0.299745;0.604380;,
  -0.000001;-0.000000;-1.000000;,
  0.358198;-0.916536;-0.177920;,
  0.358207;-0.916533;-0.177916;,
  0.000000;0.000000;-1.000000;,
  0.693036;0.270854;-0.668087;,
  0.580842;0.000000;0.814017;,
  0.348513;0.000000;0.937304;,
  0.379430;0.148289;0.913260;,
  0.693036;0.270853;0.668086;,
  0.250203;0.097785;0.963243;,
  0.414545;-0.000002;-0.910029;,
  0.787258;-0.000001;-0.616624;,
  0.693035;0.270853;-0.668088;,
  0.379429;0.148289;-0.913260;,
  0.250202;0.097784;-0.963243;,
  0.991308;0.000002;0.131564;,
  0.920094;0.000002;0.391697;,
  0.908150;-0.000002;-0.418644;;
  144;
  4;2,0,1,4;,
  4;1,0,3,5;,
  3;0,2,6;,
  3;0,7,3;,
  3;4,1,8;,
  3;1,5,8;,
  4;2,4,9,11;,
  4;10,5,3,12;,
  3;9,4,8;,
  3;8,5,10;,
  3;6,2,11;,
  3;12,3,7;,
  3;13,9,8;,
  3;8,10,14;,
  3;15,13,8;,
  3;14,15,8;,
  4;9,13,16,11;,
  4;17,14,10,12;,
  4;16,13,15,20;,
  4;15,14,17,20;,
  3;11,16,18;,
  3;17,12,19;,
  3;18,16,20;,
  3;20,17,19;,
  4;22,23,21,26;,
  3;24,25,25;,
  4;29,27,28,35;,
  4;31,26,30,34;,
  4;32,23,22,41;,
  3;27,33,28;,
  4;22,26,31,41;,
  3;36,95,96;,
  4;28,36,37,35;,
  3;38,38,39;,
  4;40,31,34,48;,
  4;42,32,41,53;,
  4;44,45,43,49;,
  4;46,47,97,98;,
  4;43,45,47,46;,
  4;41,31,40,53;,
  4;51,52,50,49;,
  4;52,51,99,100;,
  4;99,51,46,98;,
  4;51,49,43,46;,
  4;101,6,54,55;,
  4;55,56,7,101;,
  4;54,6,102,57;,
  4;7,56,58,103;,
  4;55,54,59,60;,
  4;60,61,56,55;,
  4;62,30,26,21;,
  4;63,63,63,63;,
  4;59,54,57,64;,
  4;56,61,65,58;,
  4;66,61,60,67;,
  4;67,60,59,68;,
  4;102,18,69,57;,
  4;70,19,103,58;,
  4;62,62,71,71;,
  4;72,25,25,72;,
  4;73,65,61,66;,
  4;104,19,70,74;,
  4;69,18,104,74;,
  4;57,69,75,64;,
  4;76,70,58,65;,
  4;74,70,76,77;,
  4;75,69,74,77;,
  4;78,76,65,73;,
  4;71,71,79,79;,
  3;105,106,107;,
  3;107,106,89;,
  3;107,89,108;,
  3;89,80,108;,
  3;93,88,27;,
  3;88,87,27;,
  3;27,87,33;,
  3;87,82,33;,
  3;82,81,33;,
  4;83,83,83,83;,
  3;96,109,36;,
  3;109,110,36;,
  3;110,91,36;,
  3;91,90,36;,
  3;90,94,36;,
  4;50,111,44,49;,
  4;84,38,38,84;,
  3;108,80,85;,
  3;80,92,85;,
  3;92,112,85;,
  3;112,113,85;,
  4;86,86,114,114;,
  4;115,115,86,86;,
  3;64,116,59;,
  3;116,117,59;,
  3;117,68,59;,
  4;118,119,119,120;,
  3;76,78,77;,
  3;78,121,77;,
  3;121,122,77;,
  4;123,123,124,125;,
  3;75,126,64;,
  3;126,127,64;,
  3;127,116,64;,
  3;77,122,75;,
  3;122,128,75;,
  3;128,126,75;,
  3;118,120,62;,
  3;120,62,62;,
  3;62,62,62;,
  3;62,62,62;,
  3;62,62,62;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;114,114,114;,
  3;114,114,114;,
  3;114,114,114;,
  3;114,125,114;,
  3;125,124,114;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;,
  3;83,83,83;;
 }
 MeshTextureCoords {
  175;
  0.406711;0.875000;,
  0.375000;0.750000;,
  0.437500;0.812500;,
  0.453356;0.875000;,
  0.500000;0.789714;,
  0.500000;0.832357;,
  0.375000;0.875000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.437500;0.937500;,
  0.375000;1.000000;,
  0.562500;0.812500;,
  0.625000;0.750000;,
  0.500000;0.917643;,
  0.543075;0.875000;,
  0.562500;0.937500;,
  0.500000;0.960286;,
  0.586150;0.875000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.625000;0.875000;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.025000;,
  0.375000;0.025000;,
  0.401660;0.776660;,
  0.375000;0.750000;,
  0.401660;0.750000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.437500;0.025000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.437500;0.500000;,
  0.375000;0.500000;,
  0.437500;0.250000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.598340;0.750000;,
  0.625000;0.750000;,
  0.598340;0.776660;,
  0.500000;0.025000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.875000;0.025000;,
  0.875000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.025000;,
  0.562500;0.250000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.562500;0.025000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.062500;,
  0.125000;0.062500;,
  0.375000;0.687500;,
  0.500000;0.687500;,
  0.375000;0.000000;,
  0.375000;0.062500;,
  0.625000;0.687500;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.125000;0.000000;,
  0.375000;0.725000;,
  0.625000;0.725000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.125000;,
  0.625000;0.625000;,
  0.500000;0.573907;,
  0.375000;0.573907;,
  0.125000;0.176093;,
  0.250000;0.176093;,
  0.500000;0.000000;,
  0.500000;0.062500;,
  0.750000;0.062500;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.062500;,
  0.125000;0.085371;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.067249;,
  0.401660;0.680250;,
  0.375000;0.664629;,
  0.625000;0.573907;,
  0.625000;0.000000;,
  0.625000;0.062500;,
  0.500000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.125000;,
  0.625000;0.125000;,
  0.750000;0.176093;,
  0.875000;0.176093;,
  0.500000;0.000000;,
  0.500000;0.056426;,
  0.375000;1.000000;,
  0.401660;0.892481;,
  0.500000;1.000000;,
  0.500000;0.928058;,
  0.375000;0.567460;,
  0.383431;0.572400;,
  0.396890;0.666736;,
  0.465385;0.613084;,
  0.500000;0.627416;,
  0.525011;0.963753;,
  0.500166;0.972232;,
  0.478418;0.964685;,
  0.499780;0.967904;,
  0.539545;0.611043;,
  0.594039;0.648506;,
  0.607238;0.577868;,
  0.625000;0.567460;,
  0.875000;0.000000;,
  0.625000;0.664629;,
  0.598340;0.680250;,
  0.625000;1.000000;,
  0.598340;0.892481;,
  0.625000;0.067249;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.085371;,
  0.375000;0.133082;,
  0.326715;0.176093;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.071139;,
  0.375000;0.074137;,
  0.663651;0.176093;,
  0.625000;0.144796;,
  0.625000;0.000000;,
  0.625000;0.074137;,
  0.500000;0.176093;,
  0.458533;0.176093;,
  0.553035;0.176093;,
  0.125000;0.000000;,
  0.227780;0.074137;,
  0.181054;0.089817;,
  0.125000;0.182540;,
  0.181054;0.178477;,
  0.875000;0.182540;,
  0.818946;0.178477;,
  0.875000;0.000000;,
  0.818946;0.089817;,
  0.772220;0.074137;,
  0.499780;0.826905;,
  0.559249;0.855213;,
  0.500166;0.991177;,
  0.599991;0.971339;,
  0.562500;1.000000;,
  0.586066;0.915971;,
  0.625000;1.000000;,
  0.567541;0.949346;,
  0.578700;0.944730;,
  0.578700;0.949910;,
  0.599991;0.939796;,
  0.435384;0.855584;,
  0.413494;0.916050;,
  0.400340;0.939720;,
  0.421631;0.949817;,
  0.426928;0.946910;,
  0.421631;0.944644;,
  0.375000;1.000000;,
  0.400340;0.971221;,
  0.437500;1.000000;,
  0.500000;1.000000;;
 }
}
