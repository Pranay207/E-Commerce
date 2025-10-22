import streamlit as st
import subprocess
import os

st.set_page_config(page_title="E-Commerce Search Engine", page_icon="🛍️")
st.title("🛒 E-Commerce Product Catalog Search Engine")

# Absolute path of products.txt
data_file = os.path.join(os.path.dirname(__file__), "products.txt")

# Compile C code if not compiled
if not os.path.exists("ecommerce"):
    st.info("🔧 Compiling C code...")
    try:
        subprocess.run(f"gcc main.c -o ecommerce", shell=True, check=True)
        st.success("✅ Compilation successful!")
    except subprocess.CalledProcessError as e:
        st.error(f"❌ Compilation failed:\n{e}")
        st.stop()

# Input box
query = st.text_input("Enter product name to search:")

if st.button("Search Product") and query.strip():
    try:
        process = subprocess.Popen(
            ["./ecommerce", data_file],  # pass products.txt path as argument
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        output, error = process.communicate(query + "\n")
        if process.returncode != 0:
            st.error(f"⚠️ Error running C program:\n{error}")
        else:
            st.code(output)
    except FileNotFoundError:
        st.error("❌ Executable not found. Compilation might have failed.")

