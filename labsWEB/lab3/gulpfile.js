const { src, dest, parallel } = require("gulp");
const pug = require("gulp-pug");
const uglify = require("gulp-uglify");
const babel = require("gulp-babel");
const less = require("gulp-less");
const clean_css = require("gulp-clean-css");
const fse = require('fs-extra');

// Copying public folders
try {
    console.log("Public/certificate folder: ");
    fse.copySync("./public/certificate", "./dist_gulp/public/certificate", { overwrite: true });
    console.log('Done!');
} catch (err) {
    console.error(err)
}

// Routes import
try {
    console.log("Routes folder: ");
    fse.copySync("./public/build/routes", "./dist_gulp/routes", { overwrite: true });
    console.log('Done!');
} catch (err) {
    console.error(err)
}

// Utils folder import
try {
    console.log("Utils folder: ");
    fse.copySync("./utils", "./dist_gulp/utils", { overwrite: true });
    console.log('Done!');
} catch (err) {
    console.error(err)
}

// Server file import
try {
    console.log("Server.js: ");
    fse.copySync("./server.js", "./dist_gulp/server.js", { overwrite: true });
    console.log('Done!');
} catch (err) {
    console.error(err)
}

// Database import
try {
    console.log("Database.json: ");
    fse.copySync("./storage/database.json", "./dist_gulp/storage/database.json", { overwrite: true });
    console.log('Done!');
} catch (err) {
    console.error(err)
}

paths = {
    less: {
        src: "public/stylesheets/*.less",
        dest: "dist_gulp/public/stylesheets"
    },
    pug: {
        src: "public/build/gulp_views/*.pug",
        dest: "dist_gulp/public/views"
    },
    js: {
        src: "public/build/scripts/*.js",
        dest: "dist_gulp/public/scripts"
    }
}

function build_less()
{
    return src(paths.less.src)
        .pipe(less())
        .pipe(clean_css())
        .pipe(dest(paths.less.dest));
}

function build_pug()
{
    return src(paths.pug.src)
        .pipe(pug())
        .pipe(dest(paths.pug.dest));
}

function build_js()
{
    return src(paths.js.src)
        .pipe(babel())
        .pipe(uglify())
        .pipe(dest(paths.js.dest));
}

exports.default = parallel(build_less, build_pug, build_js)