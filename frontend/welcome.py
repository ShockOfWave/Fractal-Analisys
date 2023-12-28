import streamlit as st
from src.utils.security import check_password

if not check_password():
    st.stop()

st.set_page_config(
    page_title="TDA analysis",
    page_icon="🌼",
)

st.write("# Welcome to application")

st.markdown(
    """
    This application was created to make easier TDA calculation created by out lab 🔥

    **Select any page to make necessary calculations**

    ### About us
    - We are from [ITMO University](https://itmo.ru) and
     [Infochemistry Scientific Center (ISC)](https://infochemistry.ru)
    """
)
