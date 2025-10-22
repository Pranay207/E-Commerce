import streamlit as st
import subprocess

st.set_page_config(page_title="E-Commerce Search Engine", page_icon="🛍️")

st.title("🛒 E-Commerce Product Catalog Search Engine")
st.write("This demo runs the C-based Bloom Filter + Hash Table search engine.")

# Input box
query = st.text_input("Enter product name to search:")

if st.button("Search Product"):
    if query.strip():
        # Run your C executable
        process = subprocess.Popen(
            ["./ecommerce"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
        )
        output, _ = process.communicate(query + "\n")
        st.code(output)
    else:
        st.warning("Please enter a product name.")

