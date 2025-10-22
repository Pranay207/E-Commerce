import streamlit as st
import subprocess
import os

st.set_page_config(page_title="E-Commerce Search Engine", page_icon="🛍️")
st.title("🛒 E-Commerce Product Catalog Search Engine")

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
C_FILE = os.path.join(BASE_DIR, "main.c")
EXECUTABLE = os.path.join(BASE_DIR, "ecommerce")

# Compile C code if executable not exists
if not os.path.exists(EXECUTABLE):
    st.info("🔧 Compiling C program...")
    try:
        subprocess.run(f"gcc {C_FILE} -o {EXECUTABLE}", shell=True, check=True)
        st.success("✅ Compilation successful!")
    except subprocess.CalledProcessError as e:
        st.error(f"❌ Compilation failed:\n{e}")
        st.stop()

# Input box
query = st.text_input("Enter product name:")

# Run the program
if st.button("Search Product") and query.strip():
    try:
        process = subprocess.Popen(
            [EXECUTABLE],
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
