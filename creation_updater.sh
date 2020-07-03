#!/bin/bash
version=$(grep -oPm1 "(?<=<Version>)[^<]+" extern/installeur/packages/com.vendor.product/meta/package.xml)

if [[ $1 = "--version" ]]; then
	sed -i "s/${version}/${2}/g" extern/installeur/packages/com.vendor.product/meta/package.xml
	echo "Version changed to ${2}"
elif [[ $1 = "--update" ]]; then
	echo "Version not changed : ${version}"
else
	echo "version actuelle : ${version}"
	echo "Nouvelle version :"	
	read new_version
	sed -i "s/${version}/${new_version}/g" extern/installeur/packages/com.vendor.product/meta/package.xml
	echo "Version changed to ${new_version}"
fi
# echo "Création du fichier de version"
# rm packages/com.vendor.product/data/version.json
# touch packages/com.vendor.product/data/version.json
# echo "{ 
	# \"version\": \"${version}\"
# }" >> packages/com.vendor.product/data/version.json

cp Builder_Wakfu.exe extern/installeur/packages/com.vendor.product/data/

echo "Suppression de l'ancien repository ..."
rm -r repository
echo "Création du nouveau repository ..."
cd extern/installeur/
repogen.exe --verbose --update -p packages -i com.vendor.product ../../repository 
cd -
echo "Création du fichier de version ..."
touch repository/version.json
echo "{ 
	\"version\": \"${version}\"
}" >> repository/version.json

if  [[ $1 = "--commit" ]]; then
	echo "Copie des fichiers dans le repo git..."
	rm -r ../../../mankio.github.io/repository/
	cp -r repository/ ../../../mankio.github.io/
    cd ../../../mankio.github.io/
	eval $(ssh-agent -s)
	ssh-add C:/Users/ugovo/.ssh/id_rsa_mankio
	git add *
	git commit -m "update to ${version}"
	git push
	cd -
fi