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
 237;
 -0.05289;-3.97470;5.42800;,
 -0.22322;0.24290;-0.01242;,
 -3.89249;-3.59491;5.81841;,
 -3.26363;-16.56632;-1.96885;,
 -4.75756;-18.25556;2.40434;,
 -5.12132;-13.15003;1.66390;,
 -1.79201;-12.35741;-3.34612;,
 -2.48364;-20.66703;-1.46879;,
 -4.75756;-18.25556;2.40434;,
 -3.56903;-15.28213;6.54309;,
 -5.12132;-13.15003;1.66390;,
 -3.56903;-15.28213;6.54309;,
 -4.75756;-18.25556;2.40434;,
 -1.84444;-18.51277;7.66905;,
 -3.56903;-15.28213;6.54309;,
 -1.84444;-18.51277;7.66905;,
 -0.45209;-12.72986;7.54588;,
 -6.04311;-5.38397;-1.81195;,
 -5.00079;-8.21899;1.27638;,
 -6.09330;-4.68371;2.55865;,
 -0.22322;0.24290;-0.01242;,
 -6.41916;-1.27636;-1.37004;,
 -5.81823;-1.26542;2.72943;,
 -6.04311;-5.38397;-1.81195;,
 -6.09330;-4.68371;2.55865;,
 -6.41916;-1.27636;-1.37004;,
 -6.04311;-5.38397;-1.81195;,
 -6.41916;-1.27636;-1.37004;,
 -5.04459;-0.24190;-4.90504;,
 -2.27156;-5.12571;-6.16539;,
 -6.41916;-1.27636;-1.37004;,
 -5.81823;-1.26542;2.72943;,
 -5.81823;-1.26542;2.72943;,
 -6.09330;-4.68371;2.55865;,
 -3.89249;-3.59491;5.81841;,
 -3.89249;-3.59491;5.81841;,
 -5.00079;-8.21899;1.27638;,
 -3.68033;-10.04438;4.96322;,
 -1.21940;-23.32495;7.65106;,
 3.55014;-17.94201;6.02980;,
 -1.84444;-18.51277;7.66905;,
 -2.27156;-5.12571;-6.16539;,
 -5.04459;-0.24190;-4.90504;,
 -1.80324;0.03541;-6.75493;,
 3.92699;-6.16735;-2.33325;,
 3.01049;-10.57296;-1.61447;,
 1.01708;-9.08048;-4.00890;,
 4.04827;-6.23074;2.69301;,
 3.50154;-9.72403;3.20674;,
 3.01049;-10.57296;-1.61447;,
 -1.80324;0.03541;-6.75493;,
 -0.22322;0.24290;-0.01242;,
 2.02972;-1.00179;-5.96795;,
 1.75362;-16.26690;-2.07531;,
 4.25684;-13.39232;0.74964;,
 4.39455;-17.04419;1.29210;,
 1.74187;-20.98443;-1.43570;,
 4.08942;-21.15847;1.84407;,
 4.08942;-21.15847;1.84407;,
 4.39455;-17.04419;1.29210;,
 3.55014;-17.94201;6.02980;,
 4.25684;-13.39232;0.74964;,
 3.47781;-12.98335;5.22816;,
 4.52908;-1.91045;2.82734;,
 4.78122;-1.82531;-2.25553;,
 -0.22322;0.24290;-0.01242;,
 -0.22322;0.24290;-0.01242;,
 4.78122;-1.82531;-2.25553;,
 2.02972;-1.00179;-5.96795;,
 4.78122;-1.82531;-2.25553;,
 3.92699;-6.16735;-2.33325;,
 2.24350;-5.19394;-5.33519;,
 2.02972;-1.00179;-5.96795;,
 2.24350;-5.19394;-5.33519;,
 -2.27156;-5.12571;-6.16539;,
 -1.80324;0.03541;-6.75493;,
 2.02972;-1.00179;-5.96795;,
 2.24350;-5.19394;-5.33519;,
 4.04827;-6.23074;2.69301;,
 3.92699;-6.16735;-2.33325;,
 4.52908;-1.91045;2.82734;,
 4.78122;-1.82531;-2.25553;,
 4.04827;-6.23074;2.69301;,
 3.01049;-10.57296;-1.61447;,
 3.92699;-6.16735;-2.33325;,
 -1.79201;-12.35741;-3.34612;,
 -3.42082;-9.23726;-3.19878;,
 1.01708;-9.08048;-4.00890;,
 -0.22322;0.24290;-0.01242;,
 -0.05289;-3.97470;5.42800;,
 4.52908;-1.91045;2.82734;,
 4.04827;-6.23074;2.69301;,
 4.52908;-1.91045;2.82734;,
 -0.05289;-3.97470;5.42800;,
 -5.04459;-0.24190;-4.90504;,
 -6.41916;-1.27636;-1.37004;,
 -0.22322;0.24290;-0.01242;,
 -0.22322;0.24290;-0.01242;,
 -5.81823;-1.26542;2.72943;,
 -3.89249;-3.59491;5.81841;,
 -0.22322;0.24290;-0.01242;,
 -1.80324;0.03541;-6.75493;,
 -5.04459;-0.24190;-4.90504;,
 -6.09330;-4.68371;2.55865;,
 -5.00079;-8.21899;1.27638;,
 -3.89249;-3.59491;5.81841;,
 -3.42082;-9.23726;-3.19878;,
 -6.04311;-5.38397;-1.81195;,
 -2.27156;-5.12571;-6.16539;,
 3.02780;-29.89782;2.52722;,
 -1.56727;-30.35383;3.09794;,
 0.37927;-29.19326;-0.47700;,
 3.02780;-29.89782;2.52722;,
 2.42191;-29.84326;6.35465;,
 -1.56727;-30.35383;3.09794;,
 -0.05289;-3.97470;5.42800;,
 -3.36773;-26.16116;4.38911;,
 -1.89753;-25.77887;-0.24891;,
 -1.56727;-30.35383;3.09794;,
 -3.36773;-26.16116;4.38911;,
 -1.12263;-28.49203;7.26719;,
 -1.21940;-23.32495;7.65106;,
 -3.36773;-26.16116;4.38911;,
 -1.56727;-30.35383;3.09794;,
 2.24951;-26.13066;0.21475;,
 0.37927;-29.19326;-0.47700;,
 -1.89753;-25.77887;-0.24891;,
 2.24951;-26.13066;0.21475;,
 3.02780;-29.89782;2.52722;,
 0.37927;-29.19326;-0.47700;,
 3.03959;-26.05186;5.70787;,
 3.02780;-29.89782;2.52722;,
 2.24951;-26.13066;0.21475;,
 3.02780;-29.89782;2.52722;,
 3.03959;-26.05186;5.70787;,
 2.42191;-29.84326;6.35465;,
 -1.89753;-25.77887;-0.24891;,
 -2.48364;-20.66703;-1.46879;,
 1.74187;-20.98443;-1.43570;,
 -1.56727;-30.35383;3.09794;,
 2.42191;-29.84326;6.35465;,
 -1.12263;-28.49203;7.26719;,
 3.47781;-12.98335;5.22816;,
 -0.25389;-9.42202;6.56812;,
 -0.45209;-12.72986;7.54588;,
 3.55014;-17.94201;6.02980;,
 3.47781;-12.98335;5.22816;,
 -0.45209;-12.72986;7.54588;,
 -1.84444;-18.51277;7.66905;,
 -1.89753;-25.77887;-0.24891;,
 0.37927;-29.19326;-0.47700;,
 -1.56727;-30.35383;3.09794;,
 -3.68033;-10.04438;4.96322;,
 -0.25389;-9.42202;6.56812;,
 -0.05289;-3.97470;5.42800;,
 -1.12263;-28.49203;7.26719;,
 3.03959;-26.05186;5.70787;,
 -1.21940;-23.32495;7.65106;,
 2.42191;-29.84326;6.35465;,
 3.03959;-26.05186;5.70787;,
 -1.79201;-12.35741;-3.34612;,
 -5.12132;-13.15003;1.66390;,
 -3.42082;-9.23726;-3.19878;,
 -5.12132;-13.15003;1.66390;,
 -5.00079;-8.21899;1.27638;,
 -3.42082;-9.23726;-3.19878;,
 -5.12132;-13.15003;1.66390;,
 -3.68033;-10.04438;4.96322;,
 -5.00079;-8.21899;1.27638;,
 -3.68033;-10.04438;4.96322;,
 -3.68033;-10.04438;4.96322;,
 -0.45209;-12.72986;7.54588;,
 -0.25389;-9.42202;6.56812;,
 -3.56903;-15.28213;6.54309;,
 -1.79201;-12.35741;-3.34612;,
 1.01708;-9.08048;-4.00890;,
 3.01049;-10.57296;-1.61447;,
 1.75362;-16.26690;-2.07531;,
 3.01049;-10.57296;-1.61447;,
 1.75362;-16.26690;-2.07531;,
 3.01049;-10.57296;-1.61447;,
 4.25684;-13.39232;0.74964;,
 4.25684;-13.39232;0.74964;,
 3.50154;-9.72403;3.20674;,
 3.47781;-12.98335;5.22816;,
 -3.42082;-9.23726;-3.19878;,
 -2.27156;-5.12571;-6.16539;,
 1.01708;-9.08048;-4.00890;,
 3.47781;-12.98335;5.22816;,
 3.50154;-9.72403;3.20674;,
 -0.25389;-9.42202;6.56812;,
 -6.04311;-5.38397;-1.81195;,
 -3.42082;-9.23726;-3.19878;,
 -5.00079;-8.21899;1.27638;,
 -2.27156;-5.12571;-6.16539;,
 2.24350;-5.19394;-5.33519;,
 1.01708;-9.08048;-4.00890;,
 3.92699;-6.16735;-2.33325;,
 1.01708;-9.08048;-4.00890;,
 2.24350;-5.19394;-5.33519;,
 -0.05289;-3.97470;5.42800;,
 -0.25389;-9.42202;6.56812;,
 3.50154;-9.72403;3.20674;,
 -0.05289;-3.97470;5.42800;,
 3.50154;-9.72403;3.20674;,
 4.04827;-6.23074;2.69301;,
 -2.48364;-20.66703;-1.46879;,
 -4.02338;-22.35890;2.76490;,
 -4.75756;-18.25556;2.40434;,
 -1.89753;-25.77887;-0.24891;,
 -4.02338;-22.35890;2.76490;,
 -1.89753;-25.77887;-0.24891;,
 -3.36773;-26.16116;4.38911;,
 -4.02338;-22.35890;2.76490;,
 -1.21940;-23.32495;7.65106;,
 1.74187;-20.98443;-1.43570;,
 2.24951;-26.13066;0.21475;,
 -1.89753;-25.77887;-0.24891;,
 2.24951;-26.13066;0.21475;,
 1.74187;-20.98443;-1.43570;,
 4.08942;-21.15847;1.84407;,
 4.08942;-21.15847;1.84407;,
 3.55014;-17.94201;6.02980;,
 3.40890;-22.09042;6.31650;,
 3.03959;-26.05186;5.70787;,
 2.24951;-26.13066;0.21475;,
 3.03959;-26.05186;5.70787;,
 -3.26363;-16.56632;-1.96885;,
 1.75362;-16.26690;-2.07531;,
 -2.48364;-20.66703;-1.46879;,
 -1.79201;-12.35741;-3.34612;,
 -2.48364;-20.66703;-1.46879;,
 1.75362;-16.26690;-2.07531;,
 1.74187;-20.98443;-1.43570;,
 3.40890;-22.09042;6.31650;,
 3.55014;-17.94201;6.02980;,
 -1.21940;-23.32495;7.65106;;
 
 96;
 3;0,1,2;,
 3;3,4,5;,
 3;3,5,6;,
 3;4,3,7;,
 3;8,9,10;,
 3;11,12,13;,
 3;14,15,16;,
 3;17,18,19;,
 3;20,21,22;,
 3;23,24,25;,
 3;26,27,28;,
 3;29,26,28;,
 3;30,24,31;,
 3;32,33,34;,
 3;35,36,37;,
 3;38,39,40;,
 3;41,42,43;,
 3;44,45,46;,
 3;47,48,49;,
 3;50,51,52;,
 3;53,54,55;,
 3;56,53,55;,
 3;56,55,57;,
 3;58,59,60;,
 3;59,61,62;,
 3;59,62,60;,
 3;63,64,65;,
 3;66,67,68;,
 3;69,70,71;,
 3;72,73,74;,
 3;72,74,75;,
 3;76,69,77;,
 3;78,79,80;,
 3;81,80,79;,
 3;82,83,84;,
 3;85,86,87;,
 3;88,89,90;,
 3;91,92,93;,
 3;94,95,96;,
 3;97,98,99;,
 3;100,101,102;,
 3;103,104,105;,
 3;106,107,108;,
 3;109,110,111;,
 3;112,113,114;,
 3;115,35,37;,
 3;116,117,118;,
 3;119,120,121;,
 3;120,122,123;,
 3;124,125,126;,
 3;127,128,129;,
 3;130,131,132;,
 3;133,134,135;,
 3;136,137,138;,
 3;139,140,141;,
 3;142,143,144;,
 3;145,146,147;,
 3;145,147,148;,
 3;149,150,151;,
 3;152,153,154;,
 3;155,156,157;,
 3;158,159,155;,
 3;160,161,162;,
 3;163,164,165;,
 3;166,167,168;,
 3;169,10,9;,
 3;170,171,172;,
 3;171,170,173;,
 3;174,175,176;,
 3;177,174,178;,
 3;179,180,181;,
 3;182,183,184;,
 3;48,181,49;,
 3;185,186,187;,
 3;188,189,190;,
 3;191,192,193;,
 3;194,195,196;,
 3;197,198,199;,
 3;200,201,202;,
 3;203,204,205;,
 3;206,207,208;,
 3;207,206,209;,
 3;210,211,212;,
 3;213,214,13;,
 3;213,13,12;,
 3;214,213,119;,
 3;215,216,217;,
 3;218,219,220;,
 3;221,222,223;,
 3;221,224,225;,
 3;221,223,226;,
 3;227,228,229;,
 3;228,227,230;,
 3;231,232,233;,
 3;234,235,236;,
 3;234,157,156;;
 
 MeshMaterialList {
  7;
  96;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.440920;0.449680;0.472310;1.000000;;
   23.000000;
   0.700000;0.700000;0.700000;;
   0.253680;0.258720;0.271740;;
  }
  Material {
   0.144000;0.144000;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.326400;0.332800;0.571200;1.000000;;
   31.000000;
   0.350000;0.350000;0.350000;;
   0.097920;0.099840;0.171360;;
  }
  Material {
   0.298000;0.245000;0.251000;1.000000;;
   46.000000;
   0.710000;0.710000;0.710000;;
   0.417200;0.343000;0.351400;;
  }
  Material {
   0.542400;0.545600;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.097600;0.097600;0.097600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;1.000000;0.898000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;1.000000;0.898000;;
  }
 }
 MeshNormals {
  75;
  0.074249;0.971726;0.224134;,
  -0.962570;-0.230122;0.143186;,
  -0.753686;0.140844;0.641966;,
  -0.022885;-0.997956;0.059663;,
  -0.893937;-0.203992;-0.399079;,
  -0.984288;-0.176146;0.012253;,
  -0.784552;0.026314;0.619504;,
  -0.258118;0.960604;0.103030;,
  -0.745381;-0.120076;-0.655736;,
  -0.096334;0.941962;0.321603;,
  -0.912490;-0.257727;-0.317708;,
  0.100830;0.800726;0.590483;,
  -0.946551;-0.152077;0.284453;,
  0.217430;0.457563;0.862183;,
  -0.172454;-0.096329;-0.980296;,
  0.313241;-0.035877;0.948996;,
  0.000568;0.177391;0.984140;,
  -0.248157;-0.277402;-0.928152;,
  0.207189;0.914731;0.346900;,
  0.312781;-0.399190;-0.861868;,
  0.420983;-0.133345;-0.897213;,
  0.969598;-0.042584;-0.240970;,
  0.341550;0.046689;0.938703;,
  0.587013;-0.243871;-0.771973;,
  0.318646;0.944749;-0.076909;,
  0.377291;0.926016;-0.012067;,
  0.918909;-0.236861;-0.315442;,
  -0.496189;-0.170180;-0.851373;,
  0.973197;-0.124228;0.193532;,
  -0.959102;-0.227186;0.168848;,
  0.715964;-0.141747;-0.683596;,
  0.082529;-0.988660;-0.125464;,
  -0.065014;-0.970588;0.231801;,
  -0.489765;-0.087263;0.867476;,
  -0.703746;-0.520226;0.483846;,
  0.213911;0.290035;0.932803;,
  -0.865107;-0.309468;-0.394739;,
  -0.376203;-0.801399;-0.465006;,
  0.993812;-0.111050;0.002379;,
  0.988360;-0.067558;0.136312;,
  0.835686;0.176076;0.520217;,
  0.900497;0.149306;0.408427;,
  -0.991134;-0.041522;-0.126213;,
  -0.672639;-0.328080;-0.663265;,
  0.839922;-0.161809;-0.518024;,
  0.973488;0.055171;-0.221985;,
  -0.985527;-0.157081;0.063738;,
  0.453983;-0.184573;-0.871684;,
  0.979621;-0.130930;-0.152313;,
  -0.897216;-0.074197;-0.435314;,
  -0.996765;-0.021920;-0.077321;,
  -0.932834;0.057293;0.355723;,
  -0.850045;-0.158437;0.502316;,
  0.095498;0.994019;-0.052968;,
  0.986224;-0.010150;0.165101;,
  0.915552;-0.139834;-0.377108;,
  0.405183;-0.111922;-0.907359;,
  0.934210;-0.145242;0.325817;,
  0.520323;-0.084331;0.849795;,
  0.312281;-0.109092;0.943705;,
  -0.181841;0.979895;0.082097;,
  0.087776;-0.128103;0.987869;,
  -0.882982;-0.425364;-0.198517;,
  -0.850410;-0.035238;0.524939;,
  0.440018;-0.066433;-0.895528;,
  0.065881;-0.130489;-0.989258;,
  0.965264;-0.104514;-0.239462;,
  0.978673;-0.132691;0.156818;,
  -0.008647;-0.163919;-0.986436;,
  0.336770;0.027015;0.941199;,
  0.331036;-0.039982;0.942771;,
  0.288596;0.115130;0.950504;,
  0.415803;-0.279084;-0.865575;,
  -0.007695;-0.218046;-0.975908;,
  0.290840;-0.057971;0.955014;;
  96;
  3;13,0,11;,
  3;49,5,42;,
  3;49,42,27;,
  3;5,49,4;,
  3;5,6,42;,
  3;6,5,33;,
  3;6,33,16;,
  3;10,1,12;,
  3;0,7,9;,
  3;10,12,50;,
  3;10,50,8;,
  3;17,10,8;,
  3;50,12,51;,
  3;51,12,52;,
  3;52,1,2;,
  3;15,22,33;,
  3;17,8,14;,
  3;26,44,19;,
  3;28,41,44;,
  3;53,0,24;,
  3;20,45,21;,
  3;47,20,21;,
  3;47,21,48;,
  3;48,21,54;,
  3;21,45,40;,
  3;21,40,54;,
  3;18,25,0;,
  3;0,25,24;,
  3;55,26,23;,
  3;56,23,17;,
  3;56,17,14;,
  3;56,55,23;,
  3;28,26,57;,
  3;55,57,26;,
  3;28,44,26;,
  3;27,43,19;,
  3;0,13,18;,
  3;58,57,59;,
  3;60,7,0;,
  3;0,9,11;,
  3;0,53,60;,
  3;12,1,52;,
  3;43,10,17;,
  3;31,3,37;,
  3;31,32,3;,
  3;59,61,61;,
  3;29,36,62;,
  3;29,34,63;,
  3;34,29,62;,
  3;30,64,65;,
  3;30,66,64;,
  3;38,66,30;,
  3;66,38,67;,
  3;65,68,47;,
  3;3,32,34;,
  3;40,35,16;,
  3;22,40,16;,
  3;22,16,33;,
  3;36,37,62;,
  3;2,35,13;,
  3;69,70,15;,
  3;71,70,69;,
  3;27,42,43;,
  3;42,1,43;,
  3;42,2,1;,
  3;2,42,6;,
  3;2,16,35;,
  3;16,2,6;,
  3;72,19,44;,
  3;20,72,44;,
  3;20,44,45;,
  3;45,41,40;,
  3;41,45,44;,
  3;43,17,19;,
  3;40,41,35;,
  3;10,43,1;,
  3;17,23,19;,
  3;26,19,23;,
  3;13,35,41;,
  3;13,41,28;,
  3;4,46,5;,
  3;46,4,36;,
  3;46,36,29;,
  3;46,63,33;,
  3;46,33,5;,
  3;63,46,29;,
  3;47,30,65;,
  3;30,47,48;,
  3;48,54,39;,
  3;48,38,30;,
  3;48,39,38;,
  3;73,20,68;,
  3;20,73,27;,
  3;68,20,47;,
  3;74,22,15;,
  3;74,15,70;;
 }
 MeshTextureCoords {
  237;
  0.572700;0.245100;,
  0.579700;0.250700;,
  0.581100;0.248100;,
  0.662300;0.135600;,
  0.654600;0.133500;,
  0.653500;0.151500;,
  0.661600;0.153700;,
  0.663400;0.116400;,
  0.621600;0.128100;,
  0.608800;0.144400;,
  0.620100;0.145600;,
  0.610100;0.126900;,
  0.623300;0.109400;,
  0.611700;0.108100;,
  0.599400;0.126100;,
  0.591200;0.125800;,
  0.589700;0.143200;,
  0.639000;0.215800;,
  0.628600;0.211400;,
  0.627900;0.213400;,
  0.618200;0.259900;,
  0.629300;0.261400;,
  0.617400;0.257400;,
  0.636800;0.232700;,
  0.622700;0.235900;,
  0.635600;0.240600;,
  0.660400;0.235900;,
  0.648500;0.245100;,
  0.660000;0.247300;,
  0.670000;0.235000;,
  0.633500;0.246900;,
  0.620600;0.241600;,
  0.609000;0.238800;,
  0.611100;0.232700;,
  0.601300;0.230400;,
  0.604800;0.196300;,
  0.616600;0.195300;,
  0.604900;0.192100;,
  0.582100;0.085100;,
  0.571100;0.102500;,
  0.577600;0.104200;,
  0.677200;0.234500;,
  0.669700;0.248100;,
  0.677100;0.248400;,
  0.724300;0.189600;,
  0.724100;0.184400;,
  0.713100;0.187700;,
  0.748700;0.179000;,
  0.748500;0.171300;,
  0.736200;0.173400;,
  0.703900;0.277500;,
  0.715700;0.272300;,
  0.714900;0.271200;,
  0.721700;0.130700;,
  0.734700;0.146200;,
  0.733000;0.128600;,
  0.719900;0.111700;,
  0.730900;0.109700;,
  0.742600;0.108000;,
  0.744700;0.126900;,
  0.756200;0.125500;,
  0.746400;0.144500;,
  0.757800;0.143100;,
  0.760200;0.255800;,
  0.751000;0.254800;,
  0.750400;0.257300;,
  0.739600;0.261000;,
  0.739400;0.259100;,
  0.727300;0.264900;,
  0.732000;0.237700;,
  0.730600;0.230600;,
  0.718300;0.233600;,
  0.707400;0.245300;,
  0.706900;0.234500;,
  0.697100;0.234300;,
  0.697500;0.247200;,
  0.721400;0.250000;,
  0.719000;0.242200;,
  0.755900;0.224400;,
  0.745100;0.233200;,
  0.757200;0.230400;,
  0.747000;0.238900;,
  0.749200;0.187200;,
  0.736400;0.186400;,
  0.736800;0.190000;,
  0.690700;0.172800;,
  0.690600;0.185200;,
  0.697300;0.184000;,
  0.803100;0.242200;,
  0.803300;0.237500;,
  0.797500;0.240100;,
  0.786200;0.210500;,
  0.790600;0.217500;,
  0.788100;0.209100;,
  0.652800;0.272400;,
  0.641200;0.265200;,
  0.640700;0.266700;,
  0.590300;0.256000;,
  0.603800;0.255700;,
  0.591000;0.253500;,
  0.673500;0.281500;,
  0.673800;0.280500;,
  0.663500;0.278200;,
  0.615000;0.210900;,
  0.615600;0.208500;,
  0.602600;0.206100;,
  0.668500;0.208400;,
  0.659800;0.212400;,
  0.669000;0.210000;,
  0.713200;0.032600;,
  0.705200;0.032700;,
  0.705900;0.035100;,
  0.731200;0.027300;,
  0.740500;0.025200;,
  0.739800;0.022300;,
  0.594200;0.194700;,
  0.640500;0.057700;,
  0.650200;0.059600;,
  0.650600;0.047500;,
  0.627700;0.072400;,
  0.619900;0.054600;,
  0.616900;0.071300;,
  0.630000;0.056000;,
  0.631700;0.043300;,
  0.700600;0.063100;,
  0.694400;0.052900;,
  0.694800;0.064600;,
  0.715200;0.059100;,
  0.714400;0.047100;,
  0.706700;0.049500;,
  0.735000;0.054900;,
  0.723200;0.044600;,
  0.724600;0.056900;,
  0.733200;0.042300;,
  0.745000;0.053400;,
  0.742600;0.040500;,
  0.689600;0.081500;,
  0.690000;0.099700;,
  0.696100;0.098400;,
  0.604700;0.023700;,
  0.599100;0.024200;,
  0.604600;0.026600;,
  0.795500;0.156600;,
  0.800000;0.170700;,
  0.801200;0.156100;,
  0.793300;0.122300;,
  0.795100;0.140900;,
  0.802400;0.141400;,
  0.799400;0.121200;,
  0.671400;0.064800;,
  0.677100;0.053900;,
  0.671200;0.052900;,
  0.595100;0.183800;,
  0.587100;0.181900;,
  0.587200;0.184700;,
  0.776100;0.047300;,
  0.778400;0.065500;,
  0.783200;0.063400;,
  0.766800;0.035700;,
  0.771800;0.048600;,
  0.669300;0.171700;,
  0.661700;0.169700;,
  0.662200;0.182600;,
  0.653100;0.167400;,
  0.641900;0.177500;,
  0.652900;0.180100;,
  0.630600;0.162600;,
  0.618000;0.172800;,
  0.630000;0.174900;,
  0.607500;0.159300;,
  0.596700;0.158100;,
  0.588400;0.157200;,
  0.587300;0.167500;,
  0.598100;0.143600;,
  0.704700;0.169300;,
  0.704500;0.182000;,
  0.713100;0.179300;,
  0.704700;0.153400;,
  0.713000;0.166800;,
  0.723000;0.148500;,
  0.723700;0.164000;,
  0.735700;0.161400;,
  0.747700;0.159600;,
  0.760300;0.169600;,
  0.759300;0.158100;,
  0.690600;0.193500;,
  0.697400;0.197800;,
  0.697200;0.192500;,
  0.790600;0.156700;,
  0.788000;0.166200;,
  0.790700;0.168100;,
  0.640600;0.204800;,
  0.651200;0.202400;,
  0.640500;0.200900;,
  0.698600;0.204700;,
  0.706900;0.204800;,
  0.706800;0.202600;,
  0.726100;0.203000;,
  0.715800;0.201200;,
  0.716000;0.204400;,
  0.794300;0.190400;,
  0.794100;0.184800;,
  0.789200;0.185500;,
  0.795400;0.197900;,
  0.789100;0.191100;,
  0.789300;0.198800;,
  0.664600;0.097200;,
  0.657300;0.095300;,
  0.655900;0.114500;,
  0.665400;0.079000;,
  0.637100;0.091900;,
  0.649300;0.075500;,
  0.638900;0.073800;,
  0.625400;0.090500;,
  0.614000;0.089300;,
  0.702100;0.096700;,
  0.701200;0.078800;,
  0.695400;0.080300;,
  0.716500;0.074900;,
  0.718100;0.092800;,
  0.728600;0.090900;,
  0.740100;0.089200;,
  0.754200;0.106600;,
  0.751400;0.087900;,
  0.737500;0.071300;,
  0.726500;0.072900;,
  0.748200;0.069900;,
  0.676200;0.138900;,
  0.683500;0.139400;,
  0.683700;0.119800;,
  0.676000;0.157200;,
  0.690400;0.119200;,
  0.697500;0.137200;,
  0.696900;0.117800;,
  0.784700;0.083500;,
  0.796500;0.100900;,
  0.789900;0.082100;;
 }
}
