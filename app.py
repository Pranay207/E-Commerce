import streamlit as st
import subprocess
import os

st.set_page_config(page_title="E-Commerce Search Engine", page_icon="🛍️")

st.title("🛒 E-Commerce Product Catalog Search Engine")
st.write("This demo runs the C-based Bloom Filter + Hash Table search engine built in pure C.")

# --- Step 1: Auto compile the C code if not already compiled ---
if not os.path.exists("ecommerce"):
    st.info("🔧 Compiling C source files...")
    try:
        # Compile all C files inside src/ and include headers
        subprocess.run(["gcc", "src/*.c", "-Iinclude", "-o", "ecommerce"], shell=True, check=True)
        st.success("✅ Compilation successful! Ready to search.")
    except subprocess.CalledProcessError as e:
        st.error(f"❌ Compilation failed:\n{e}")
        st.stop()

# --- Step 2: Search input box ---
query = st.text_input("Enter product name to search:")

# --- Step 3: Run the compiled program when button clicked ---
if st.button("Search Product"):
    if query.strip():
        try:
            # Run C executable and send the query via stdin
            process = subprocess.Popen(
                ["./ecommerce"],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
            )
            output, error = process.communicate(query + "\n")

            if process.returncode != 0:
                st.error(f"⚠️ Error running C program:\n{error}")
            else:
                st.code(output, language="text")
        except FileNotFoundError:
            st.error("❌ Executable not found. Please ensure build.sh or compilation succeeded.")
    else:
        st.warning("Please enter a product name.")
