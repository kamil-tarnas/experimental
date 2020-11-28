find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -Ei ':a; s/(.*)std::size_t(.*)/\1size_t\2/; ta' {} +
