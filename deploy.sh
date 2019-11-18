#!/usr/bin/env sh

# abort on errors
set -e

cd abbexpectmore

# build
echo "##############################"
echo
echo "installing..."
echo
echo "##############################"
npm i
echo "##############################"
echo
echo "Building..."
echo
echo "##############################"
npm run build

echo "##############################"
echo
echo "Done!"
echo
echo "##############################"
# navigate into the build output directory
cd dist

# if you are deploying to a custom domain
# echo 'www.example.com' > CNAME

git init
git add -A
git commit -m 'deploy'

echo "##############################"
echo
echo "Commiting..."
echo
echo "##############################"

# if you are deploying to https://<USERNAME>.github.io
git push -f git@github.com:AbbExpectMore/AbbExpectMore.github.io.git master

cd -