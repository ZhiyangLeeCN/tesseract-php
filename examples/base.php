<?php

use Tesseract\TesseractBaseApi;
use Tesseract\PageSegMode;

$api = new TesseractBaseApi;
$api->Init("./tessdata", "eng");
if ($api->Init("./tessdata", "eng")) {
    echo "api init error.\n";
    exit;
}

$api->SetPageSegMode(PageSegMode::PSM_AUTO);
$api->SetVariable("save_best_choices", "T");

$pixs = tessPixRead("test.png");
if ($pixs === false) {
    echo "read png error.\n";
    exit;
}

$api->SetImage($pixs);

echo $api->GetUTF8Text();

tessPixDestroy($pixs);

$api->Clear();