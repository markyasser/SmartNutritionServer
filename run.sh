cd build
cmake .. 
make -j$(nproc)
cd ..
./build/SmartNutritionServer