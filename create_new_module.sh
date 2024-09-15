#!/bin/bash

PROJECT_NAME="pon-chat"

# root directory of the project
DIR=$(dirname "$(readlink -f "$0")")

MODULE_TYPE=$1
MODULE_NAME=$2

if [ -z "$MODULE_TYPE" ] || [ -z "$MODULE_NAME" ]; then
    echo "Usage: $0 [lib|app] module_name"
    exit 1
fi

if [ "$MODULE_TYPE" != "lib" ] && [ "$MODULE_TYPE" != "app" ]; then
    echo "Invalid module type. Use 'lib' or 'app'."
    exit 1
fi

if [ -d $DIR/src/${MODULE_NAME} ]; then
    echo "The module already exists"
    exit 1
fi

TEMPLATE_DIR="$DIR/templates/template_${MODULE_TYPE}_module/"

# copy the template module and rename its parts
cp -r $TEMPLATE_DIR $DIR/src/
mv $DIR/src/template_${MODULE_TYPE}_module/ $DIR/src/$MODULE_NAME
mv $DIR/src/$MODULE_NAME/include/PROJECT_NAME/MODULE_NAME $DIR/src/$MODULE_NAME/include/PROJECT_NAME/$MODULE_NAME
mv $DIR/src/$MODULE_NAME/include/PROJECT_NAME $DIR/src/$MODULE_NAME/include/$PROJECT_NAME
rm $DIR/src/$MODULE_NAME/src/.gitkeep $DIR/src/$MODULE_NAME/include/$PROJECT_NAME/$MODULE_NAME/.gitkeep

# expand 'MODULE_NAME' to the name of the module in every file of the module's folder
find $DIR/src/$MODULE_NAME -type f -exec sed -i "s/MODULE_NAME/$MODULE_NAME/g" {} \;
find $DIR/src/$MODULE_NAME -type f -exec sed -i "s/PROJECT_NAME/$PROJECT_NAME/g" {} \;

# add the module to the 'src/CMakeLists.txt' script
LINE="add_subdirectory(${MODULE_NAME})"
if [ ! $(grep $LINE $DIR/src/CMakeLists.txt) ]; then
    echo $LINE >> $DIR/src/CMakeLists.txt
fi
