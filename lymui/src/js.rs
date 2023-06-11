use napi::bindgen_prelude::*;

pub trait FromJsObject {
    fn from_js_object(object: Object) -> Result<Self>
    where
        Self: Sized;
}

pub mod prelude {
    pub use super::FromJsObject;
    pub use js_macro::FromJsObj;
    pub use napi::bindgen_prelude::{Object, Result as NapiResult, Status};
    pub use napi::Error as JsError;
}
