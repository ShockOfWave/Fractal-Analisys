import os
import uuid
import shutil
import streamlit as st
from src.calculations.lacunarity.one_file_calculation import calc_one_file
from src.utils.security import check_password
from src.utils.paths import PATH_TO_TMP_FILES_DIR, PATH_TO_TMP_ARCHIVE_DIR, PATH_TO_TMP

if not os.path.exists(PATH_TO_TMP_FILES_DIR):
    os.makedirs(PATH_TO_TMP_FILES_DIR)

if not os.path.exists(PATH_TO_TMP_ARCHIVE_DIR):
    os.makedirs(PATH_TO_TMP_ARCHIVE_DIR)

if not os.path.exists(PATH_TO_TMP):
    os.makedirs(PATH_TO_TMP)

if not check_password():
    st.stop()

st.markdown(
    """
    # Lacunarity calculation

    # One file calculation
"""
)

uploaded_file = st.file_uploader("Choose a file")

if st.button("Upload file"):
    if uploaded_file is None:
        e = FileNotFoundError("Please select file")
        st.exception(e)
    else:
        with st.spinner("Calculating..."):
            study_name = str(uploaded_file.name) + str(uuid.uuid4())
            file_path = os.path.join(PATH_TO_TMP_FILES_DIR, study_name)
            archive_path = os.path.join(PATH_TO_TMP_ARCHIVE_DIR, study_name)
            os.makedirs(file_path)

            with open(os.path.join(file_path, uploaded_file.name), "wb") as out_file:
                content = uploaded_file.read()
                out_file.write(content)

            calc_one_file(os.path.join(file_path, uploaded_file.name))

            shutil.make_archive(archive_path, "zip", file_path)

        st.success("Done!")

        st.markdown(
            """
                    ### You can download all plots in SVG format here
                    """
        )

        with open(archive_path + ".zip", "rb") as f:
            st.download_button(
                "Download ZIP", f, file_name=uploaded_file.name[:-4] + ".zip"
            )

        col1, col2 = st.columns(2)

        st.markdown(
            """
                    ### There is results
                    """
        )

        with col1:
            st.image(
                os.path.join(file_path, uploaded_file.name[:-4], "diff_coords.svg")
            )
            st.image(
                os.path.join(file_path, uploaded_file.name[:-4], "distribution_num.svg")
            )
            st.image(os.path.join(file_path, uploaded_file.name[:-4], "each_slice.svg"))
            st.image(
                os.path.join(file_path, uploaded_file.name[:-4], "each_slice_exp.svg")
            )

        with col2:
            st.image(
                os.path.join(file_path, uploaded_file.name[:-4], "fractal_slice.svg")
            )
            st.image(
                os.path.join(file_path, uploaded_file.name[:-4], "integer_coords.svg")
            )
            st.image(
                os.path.join(
                    file_path, uploaded_file.name[:-4], "square_distribution.svg"
                )
            )

st.markdown(
    """
            # Multiply files calculations
            ### Here you can upload all your txt files and get results inside archive
            """
)

uploaded_files = st.file_uploader("Choose files", accept_multiple_files=True)

if st.button("Upload files"):
    if not uploaded_files:
        e = FileNotFoundError("Please select files")
        st.exception(e)
    else:
        progress_bar = st.progress(0, text="Start calculating...")
        studies = []
        for i, up_file in enumerate(uploaded_files):
            study_name = str(up_file.name)[:-4] + "_" + str(uuid.uuid4())
            file_path = os.path.join(PATH_TO_TMP_FILES_DIR, study_name)
            archive_path = os.path.join(PATH_TO_TMP_ARCHIVE_DIR, study_name)
            os.makedirs(file_path)

            with open(os.path.join(file_path, up_file.name), "wb") as out_file:
                content = up_file.read()
                out_file.write(content)

            studies.append(study_name)
            calc_one_file(os.path.join(file_path, up_file.name))
            progress_bar.progress(
                (100 / len(uploaded_files) / 100) * (i + 1),
                text=f"Calculating {up_file.name}",
            )

        progress_bar.empty()
        st.success("Done!")

        path_to_zip = os.path.join(PATH_TO_TMP_ARCHIVE_DIR, str(uuid.uuid4()) + ".zip")

        tmp_dir = os.path.join(PATH_TO_TMP, str(uuid.uuid4()))

        for study in studies:
            shutil.copytree(
                os.path.join(PATH_TO_TMP_FILES_DIR, study),
                tmp_dir + "/",
                dirs_exist_ok=True,
            )

        shutil.make_archive(
            os.path.join(PATH_TO_TMP_ARCHIVE_DIR, tmp_dir.split(os.sep)[-1]),
            "zip",
            tmp_dir,
        )

        shutil.rmtree(tmp_dir)

        with open(
            os.path.join(PATH_TO_TMP_ARCHIVE_DIR, tmp_dir.split(os.sep)[-1]) + ".zip",
            "rb",
        ) as f:
            st.download_button(
                "Download ZIP", f, file_name=path_to_zip.split(os.sep)[-1]
            )
