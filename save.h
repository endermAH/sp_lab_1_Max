// Разбивка аргументов
// for (int i = 1; i <= argc-1 ; i++) {
//   if (strcmp("-x", argv[i]) == 0) {
//     maxLength = atoi(argv[i+1]);
//     i++;
//   } else if (strcmp("-n", argv[i]) == 0) {
//     minLength = atoi(argv[i+1]);
//     i++;
//   } else if (strcmp("-l", argv[i]) == 0) {
//     stringNumbers = true;
//   } else if (i == argc-2 || (i == argc-1 && pathCount == 0)) {
//     inputPath = argv[i];
//     pathCount++;
//   } else if (i == argc-1 && pathCount == 1) {
//     outputPath = argv[i];
//   } else {
//     fprintf(stderr, "Error - undefined key '%s'!\n", argv[i]);
//     return 0;
//   }
// }
